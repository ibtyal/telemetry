from fastapi import FastAPI, WebSocket, WebSocketDisconnect, HTTPException, Response
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse
from typing import List
from csv_handler import CSVHandler
import os

app = FastAPI()


app.add_middleware(
    CORSMiddleware,
    allow_origins=["https://siima.tech", "http://siima.tech"],  # Permitir estos orígenes
    allow_credentials=True,  # Permitir enviar cookies y credenciales
    allow_methods=["*"],  # Permitir todos los métodos HTTP (GET, POST, etc.)
    allow_headers=["*"],  # Permitir todas las cabeceras
)


# Descarga de sesiones

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

# Instancia del ConnectionManager para gestionar las conexiones activas en /ws-status
status_manager = ConnectionManager()

# Instancia del ConnectionManager para gestionar las conexiones activas en /ws-data
data_manager = ConnectionManager()

# Ruta para recibir datos desde el ESP32 y transmitirlos al frontend en /ws-status y /ws-data
@app.websocket("/ws-data")
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
            time = json_data.get("Time")
            voltage = json_data.get("Voltage")
            current = json_data.get("Current")
            rpm = json_data.get("RPM")
            distance = json_data.get("Distance")
            velocity = json_data.get("Velocity")
            soc = json_data.get("Soc")

            # Escribir una nueva fila en el CSV
            csv_handler.write_row(time, voltage, current, rpm, distance, velocity, soc)

            # Enviar los datos a los clientes conectados a /ws-status (HomePage.vue y RealTimeData.vue)
            await status_manager.send_data(json_data)

            # Enviar los datos también a los clientes conectados a /ws-data (RealTimeData.vue)
            await data_manager.send_data(json_data)

    except WebSocketDisconnect:
        print(f"Conexión cerrada, datos guardados en {csv_filename}")
        csv_handler.close_csv()

# Ruta para enviar los datos retransmitidos al frontend (HomePage.vue y RealTimeData.vue)
@app.websocket("/ws-status")
async def websocket_status(websocket: WebSocket):
    await status_manager.connect(websocket)
    try:
        while True:
            # Mantener la conexión abierta y retransmitir los datos recibidos en /ws-data
            await websocket.receive_text()  # Solo para mantener la conexión activa
    except WebSocketDisconnect:
        status_manager.disconnect(websocket)
        print("Conexión WebSocket /ws-status cerrada")