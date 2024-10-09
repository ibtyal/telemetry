#include <ModbusMaster.h>

ModbusMaster node;

const int pinEnable = 2; // Control de DE y RE

void preTransmission() {
  digitalWrite(pinEnable, HIGH);  // Activa transmisión
}

void postTransmission() {
  digitalWrite(pinEnable, LOW);  // Activa recepción
}

void setup() {
  Serial.begin(9600);
  pinMode(pinEnable, OUTPUT);
  digitalWrite(pinEnable, LOW);  // Modo recepción al iniciar
  
  node.begin(1, Serial); // Dirección del dispositivo esclavo es 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;
  
  // Leer datos del JSY-MK-229
  result = node.readHoldingRegisters(0x0100, 6);
  
  if (result == node.ku8MBSuccess) {
    float voltage = (node.getResponseBuffer(0x00) << 16 | node.getResponseBuffer(0x01)) / 10000.0;
    float current = (node.getResponseBuffer(0x02) << 16 | node.getResponseBuffer(0x03)) / 10000.0;
    
    Serial.print("Voltaje: ");
    Serial.print(voltage);
    Serial.println(" V");
    
    Serial.print("Corriente: ");
    Serial.print(current);
    Serial.println(" A");
  } else {
    Serial.println("Error leyendo los registros");
  }
  
  delay(1000);
}

