import csv
import datetime
import os

class CSVHandler:
    def __init__(self, csv_dir="../sessions"):
        # Confirms that file path exsits or create it if does not exist
        self.csv_dir = csv_dir
        os.makedirs(self.csv_dir, exist_ok=True)
        self.csv_file = None
        self.csv_writer = None

    def create_csv(self):
        # Creates a timestamp to name CSV files
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        csv_filename = f"{self.csv_dir}/{timestamp}.csv"
        
        # Opens csv file and write headers
        self.csv_file = open(csv_filename, mode='w', newline='')
        self.csv_writer = csv.writer(self.csv_file)
        self.csv_writer.writerow(['Time', 'Voltage', 'Current', 'RPM', 'Distance', 'Velocity', 'Soc'])  # CSV Headers
        
        return csv_filename

    def write_row(self, time, voltaje, current, rpm, distance, velocity, soc):
        if self.csv_writer:
            self.csv_writer.writerow([time, voltaje, current, rpm, distance, velocity, soc])

    def close_csv(self):
        if self.csv_file:
            self.csv_file.close()
