import csv
import datetime
import os

class CSVHandler:
    def __init__(self, csv_dir="../sessions"):
        # Asegurarse de que el directorio para los archivos CSV existe
        self.csv_dir = csv_dir
        os.makedirs(self.csv_dir, exist_ok=True)
        self.csv_file = None
        self.csv_writer = None

    def create_csv(self):
        # Crear un timestamp para el archivo CSV
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        csv_filename = f"{self.csv_dir}/{timestamp}.csv"
        
        # Abrir el archivo CSV y escribir los encabezados
        self.csv_file = open(csv_filename, mode='w', newline='')
        self.csv_writer = csv.writer(self.csv_file)
        self.csv_writer.writerow(['Time(sec)', 'Voltage', 'Current', 'RPM', 'Distance', 'Velocity'])  # Encabezados del CSV
        
        return csv_filename

    def write_row(self, time, voltaje, current, rpm, distance, velocity):
        if self.csv_writer:
            self.csv_writer.writerow([time, voltaje, current, rpm, distance, velocity])

    def close_csv(self):
        if self.csv_file:
            self.csv_file.close()
