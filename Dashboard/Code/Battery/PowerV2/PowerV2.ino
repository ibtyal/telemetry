#include <SoftwareSerial.h>
#include <ModbusMaster.h>

// Crear una instancia de SoftwareSerial
#define RX_PIN 10  // Pin RX del Arduino (Recibir datos desde el JSY-MK-229)
#define TX_PIN 11  // Pin TX del Arduino (Enviar datos hacia el JSY-MK-229)
SoftwareSerial mySerial(RX_PIN, TX_PIN);

// Crear una instancia de ModbusMaster
ModbusMaster node;

// Pin para controlar DE/RE en el MAX485
#define DE_RE_PIN 2

// Funciones de control para DE/RE
void preTransmission() {
  digitalWrite(DE_RE_PIN, HIGH);  // Activar modo de transmisión
}

void postTransmission() {
  digitalWrite(DE_RE_PIN, LOW);   // Activar modo de recepción
}

void setup() {
  // Configurar el pin DE/RE
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW);  // Iniciar en modo recepción

  // Iniciar la comunicación serial
  Serial.begin(9600);  // Comunicación con el monitor serial
  mySerial.begin(9600);  // Comunicación RS485 con el JSY-MK-229 usando SoftwareSerial

  // Iniciar Modbus con la instancia de SoftwareSerial
  node.begin(1, mySerial);  // Dirección del esclavo es 1 (predeterminado)
  node.preTransmission(preTransmission);   // Función para activar la transmisión
  node.postTransmission(postTransmission); // Función para activar la recepción

  Serial.println("Iniciando comunicación Modbus con JSY-MK-229...");
}

void loop() {
  uint8_t result;
  uint32_t voltage, current;

  // Leer registros de voltaje desde 0x0100 (2 registros)
  result = node.readHoldingRegisters(0x0100, 2);  // Leer 2 registros (32 bits para el voltaje)
  
  if (result == node.ku8MBSuccess) {
    // Combinar los dos registros de 16 bits en un valor de 32 bits
    voltage = node.getResponseBuffer(0x00) << 16 | node.getResponseBuffer(0x01);
    float voltageValue = voltage /100.0;  // Escalar el valor del voltaje
    Serial.print("Voltaje: ");
    Serial.print(voltageValue);
    Serial.println(" V");
  } else {
    Serial.print("Error leyendo voltaje: ");
    Serial.println(result, HEX);  // Imprimir código de error en hexadecimal
  }

  // Leer registros de corriente desde 0x0102 (2 registros)
  result = node.readHoldingRegisters(0x0102, 2);  // Leer 2 registros (32 bits para la corriente)
  
  if (result == node.ku8MBSuccess) {
    // Combinar los dos registros de 16 bits en un valor de 32 bits
    current = node.getResponseBuffer(0x00) << 16 | node.getResponseBuffer(0x01);
    float currentValue = current / 10000.0;  // Escalar el valor de la corriente
    Serial.print("Corriente: ");
    Serial.print(currentValue);
    Serial.println(" A");
  } else {
    Serial.print("Error leyendo corriente: ");
    Serial.println(result, HEX);  // Imprimir código de error en hexadecimal
  }

  delay(1000);  // Esperar un segundo antes de la siguiente lectura
}
