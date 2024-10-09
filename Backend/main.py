from fastapi import FastAPI, WebSocket, WebSocketDisconnect, Response
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse
from typing import List
from csv_handler import CSVHandler
import os

app = FastAPI()


app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Permitir estos orígenes
    allow_credentials=True,  # Permitir enviar cookies y credenciales
    allow_methods=["*"],  # Permitir todos los métodos HTTP (GET, POST, etc.)
    allow_headers=["*"],  # Permitir todas las cabeceras
)

SESSIONS_FOLDER = "../sessions"

@app.get("/sessions")
def list_sessions():
    try:
        files = os.listdir(SESSIONS_FOLDER)
        return {"files": files}
    except Exception as e:
        return {"error": str(e)}

@app.get("/download/{file_name}")
def download_file(file_name: str):
    file_path = os.path.join(SESSIONS_FOLDER, file_name)
    if os.path.exists(file_path):
        return FileResponse(file_path, media_type='application/octet-stream', filename=file_name)
    return {"error": "File not found"}


# Clase para manejar conexiones de WebSocket
class ConnectionManager:
    def __init__(self):
        self.active_connections: List[WebSocket] = []

    async def connect(self, websocket: WebSocket):
        await websocket.accept()
        self.active_connections.append(websocket)

    def disconnect(self, websocket: WebSocket):
        self.active_connections.remove(websocket)

    async def send_data(self, message: dict):
        for connection in self.active_connections:
            await connection.send_json(message)

# Instancia del ConnectionManager para gestionar las conexiones activas
manager = ConnectionManager()

# Ruta para recibir datos desde el ESP32 y guardarlos en CSV
@app.websocket("/ws-csv")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()

    # Crea un CSV Handler
    csv_handler = CSVHandler()

    # Crear un nuevo archivo CSV
    csv_filename = csv_handler.create_csv()

    try:
        while True:
            # Recibir datos en formato JSON desde el ESP32
            json_data = await websocket.receive_json()

            # Obtener datos individuales
            time = json_data.get("Time(sec)")
            voltage = json_data.get("Voltage")
            current = json_data.get("Current")
            rpm = json_data.get("RPM")
            distance = json_data.get("Distance")
            velocity = json_data.get("Velocity")

            # Escribir una nueva fila en el CSV
            csv_handler.write_row(time, voltage, current, rpm, distance, velocity)

            # Enviar los datos a los clientes conectados a /ws-data (frontend)
            await manager.send_data(json_data)

    except WebSocketDisconnect:
        print(f"Conexión cerrada, datos guardados en {csv_filename}")
        csv_handler.close_csv()

# Ruta para el frontend, que recibe los datos y los muestra en tiempo real
@app.websocket("/ws-data")
async def websocket_data(websocket: WebSocket):
    await manager.connect(websocket)
    try:
        while True:
            # Mantener la conexión abierta para enviar datos cuando lleguen
            await websocket.receive_text()  # Mantén la conexión abierta
    except WebSocketDisconnect:
        manager.disconnect(websocket)
