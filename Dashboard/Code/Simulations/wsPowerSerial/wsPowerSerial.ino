#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <ModbusMaster.h>

ModbusMaster node;

const int pinEnable = 26; // Control de DE y RE


//Declaración de parámetros para websocket
const char* websockets_server_host = "dominio o IP del servidor"; //Enter server adress
const uint16_t websockets_server_port = 1111; // Puerto

using namespace websockets;
WebsocketsClient client;

int runningTime = 0; //inicialización del tiempo


// Funciones de control para DE/RE
void preTransmission() {
  digitalWrite(pinEnable, HIGH);  // Activa transmisión
}

void postTransmission() {
  digitalWrite(pinEnable, LOW);  // Activa recepción
}

void sendData (float voltageM, float currentM) {
  //convertir valores a string
  char voltage[50]; // El voltaje podrá ser almacenado en un string de 50 caracteres
  char current[50]; // La corriente podrá ser almacenado en un string de 50 caracteres

  //generando string almacenando voltaje con 2 cifras significativas
  sprintf(voltage, "\"Voltage\": %.2f", voltageM);
  sprintf(current, "\"Current\": %.2f", currentM);
  
  //Actualizando tiempo
  runningTime++;
  
  // Generando JSON: formato esperado {"Time": 5, "Voltage": 39.81, "Current": 1.87, "RPM": 315.00, "Distance":1.00, "Velocity":5.40}
  String telemetry = "{\"Time\": ";
  telemetry += String(runningTime);
  telemetry += ", ";
  telemetry += voltage;
  telemetry += ", ";
  telemetry += current;
  telemetry += ", "
  telemetry += "\"RPM\": 315.00, \"Distance\":1.00, \"Velocity\": 5.40}"
  Serial.println(telemetry);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to SIIMA telemetry project");

  //Configuración de comunicación al JSY-MK-229 
  pinMode(pinEnable, OUTPUT);
  digitalWrite(pinEnable, LOW);  // Modo recepción al iniciar  
  node.begin(1, Serial); // Dirección del dispositivo esclavo es 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  Serial.println("Iniciando comunicación Modbus con JSY-MK-229...");


  //Configurando conexión a Wi-Fi
  Serial.println("Conectando a WiFi");
  WiFi.begin("wifi SSID", "Password");
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
}


void loop() {
  uint8_t result;
  uint32_t voltage, current;
  
  // Leer datos del JSY-MK-229
  result = node.readHoldingRegisters(0x0100, 6);
  
  if (result == node.ku8MBSuccess) {
    unsigned long voltageLecture = (node.getResponseBuffer(0x00) << 16 | node.getResponseBuffer(0x01));
    unsigned long  currentLecture = (node.getResponseBuffer(0x02) << 16 | node.getResponseBuffer(0x03));
    //como el manual indica se utiliza unsigned long, para evitar errores de lectura cuando los valores son superiores a 65,535 se utiliza unsigned long (capaz de almacenar muchos más)
  }
  
  delay(1000);
  sendData ((voltageLecture/10000.0), (currentLecture/10000.0));
}