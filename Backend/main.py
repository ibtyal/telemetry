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

@app.get("/")
def alive():
    try:
        return {"ok": True}
    except Exception as e:
        return {"error": str(e)}
    
@app.get("/sessions")
def list_sessions():
    try:
        files = os.listdir(SESSIONS_FOLDER)
        print(files)
        return {"files": files}
    except Exception as e:
        print(e)
        return {"error": str(e)}

@app.get("/download/{file_name}")
def download_file(file_name: str):
    file_path = os.path.join(SESSIONS_FOLDER, file_name)
    if os.path.exists(file_path):
        return FileResponse(file_path, media_type='application/octet-stream', filename=file_name)
    return {"error": "File not found"}


# Here starts WS data
@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    
    # Creates a CSV Handler
    csv_handler = CSVHandler()

    # Crear un nuevo archivo CSV
    csv_filename = csv_handler.create_csv()
    
    try:
        while True:
            # Receves json data
            json_data = await websocket.receive_json()
            
            # Gets individual data
            time = json_data.get("Time(sec)")
            voltaje = json_data.get("Voltage")
            current = json_data.get("Current")
            rpm = json_data.get("RPM")
            distance = json_data.get("Distance")
            velocity = json_data.get("Velocity")
            
            # Writes a new row
            csv_handler.write_row(time, voltaje, current, rpm, distance, velocity)
    
    except WebSocketDisconnect:
        print(f"Conexión cerrada, datos guardados en {csv_filename}")
        csv_handler.close_csv()
