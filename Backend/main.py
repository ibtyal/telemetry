from fastapi import FastAPI, WebSocket, WebSocketDisconnect
from typing import List
from csv_handler import CSVHandler

app = FastAPI()

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    
    # Crear un manejador de CSV
    csv_handler = CSVHandler()

    # Crear un nuevo archivo CSV
    csv_filename = csv_handler.create_csv()
    
    try:
        while True:
            # Recibir los datos JSON a través del WebSocket
            json_data = await websocket.receive_json()
            
            # Extraer la temperatura y la humedad del JSON
            time = json_data.get("Time(sec)")
            voltaje = json_data.get("Voltage")
            current = json_data.get("Current")
            rpm = json_data.get("RPM")
            distance = json_data.get("Distance")
            velocity = json_data.get("Velocity")
            
            # Escribir una nueva fila en el archivo CSV
            csv_handler.write_row(time, voltaje, current, rpm, distance, velocity)
    
    except WebSocketDisconnect:
        print(f"Conexión cerrada, datos guardados en {csv_filename}")
        csv_handler.close_csv()
