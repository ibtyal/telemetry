#include <ModbusMaster.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

// Pin definitions
const int hallSensorPin = 2;  // KY-003 signal pin (S)
volatile unsigned int pulseCount = 0;  // Counter for the pulses
unsigned long lastTime = 0;  // Stores the last time RPM was calculated
//unsigned int rpm = 0;  // Stores the calculated RPM
float distanceM = 0;
float distanceAntM = 0;
float speedM = 0;
int runningTime = 0;

unsigned long rawVoltage;
unsigned long rawCurrent;
//float voltageM;
//float currentM;

//WS configuration
const char* websockets_server_host = "siima.tech"; //Enter server adress
const uint16_t websockets_server_port = 8000; // Enter server port

using namespace websockets;
WebsocketsClient client;

ModbusMaster node;

const int pinEnable = 16; // Control de DE y RE

void sendData (float voltageM, float currentM, unsigned int rpm) {

  runningTime++;
  distanceM = distanceM + (pulseCount*1.54);
  speedM = (distanceM - distanceAntM) * (3.6); 

  //convertir valores a string
  char voltage[50]; // El voltaje podrá ser almacenado en un string de 50 caracteres
  char current[50]; // La corriente podrá ser almacenado en un string de 50 caracteres
  char distance[50]; // El voltaje podrá ser almacenado en un string de 50 caracteres
  char speed[50];

  //generando string almacenando voltaje con 2 cifras significativas
  dtostrf(voltageM, 4, 2, voltage); 
  dtostrf(currentM, 4, 2, current);  
  dtostrf(distanceM, 4, 2, distance);  
  dtostrf(speedM, 4, 2, speed);  
  // Generando JSON: formato esperado {"Time": 5, "Voltage": 39.81, "Current": 1.87, "RPM": 315.00, "Distance":1.00, "Velocity":5.40}
  String telemetry = "{\"Time\": " + String(runningTime) + ", \"Voltage\": " + voltage + ", \"Current\": " + current + ", \"RPM\": " + String(rpm) + ", \"Distance\": "+ distance + ", \"Velocity\": " + speed + ", \"Soc\": 100}";
   
  Serial.println(telemetry);

    //Values reset
  distanceAntM = distanceM;
  pulseCount = 0;  // Reset pulse count
}

// Funciones de control para DE/RE
void preTransmission() {
  digitalWrite(pinEnable, HIGH);  // Activa transmisión
}

void postTransmission() {
  digitalWrite(pinEnable, LOW);  // Activa recepción
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Serial.println("Welcome to SIIMA telemetry project");

  //Configuración Sensor efecto hall (KY-003)
  pinMode(hallSensorPin, INPUT_PULLUP);  // KY-003 has an open-drain output, use internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), countPulse, FALLING);  // Se inicializa desactivado

  // Configuración JSY-MK-229
  Serial2.begin(9600, SERIAL_8N1, 18, 17); // se utiliza otro serial para que no se interrumpa la comunicación
  pinMode(pinEnable, OUTPUT);
  digitalWrite(pinEnable, LOW);  // Modo recepción al iniciar  
  node.begin(1, Serial2); // Dirección del dispositivo esclavo es 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  Serial.println("Iniciando comunicación Modbus con JSY-MK-229...");

  //Configurando conexión WiFi
  Serial.println("Connecting to WiFi");
  WiFi.begin("Francesco", "Elbalazo");
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected to Wifi, Connecting to server.");
   //Conectando a Websockets server
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/ws-data");
  if(connected) {
   Serial.println("Connected!");
  } else {
      Serial.println("Not Connected!");
  }
}

void loop() {
  unsigned long currentTime = millis();
  uint8_t result;
  uint16_t data[6];

  // Calculate RPM every second (1000ms)
  if (currentTime - lastTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(hallSensorPin));  // Detiene el conteo de RPM
  
    // Leer registros de voltaje y corriente desde el JSY-MK-229
    result = node.readHoldingRegisters(0x0100, 6);
    
    if (result == node.ku8MBSuccess) {
      rawVoltage = (node.getResponseBuffer(0x00) << 16 | node.getResponseBuffer(0x01));
      rawCurrent = (node.getResponseBuffer(0x02) << 16 | node.getResponseBuffer(0x03));
    }
    sendData((rawVoltage / 10000.0), (rawCurrent / 10000.0), (pulseCount * 195));
    
    lastTime = currentTime;

    attachInterrupt(digitalPinToInterrupt(hallSensorPin), countPulse, FALLING);  // Rehabilita el conteo de RPM
  }
}

void countPulse() {
  pulseCount++;
}

