// Pin definitions
const int hallSensorPin = 2;  // KY-003 signal pin (S)
volatile unsigned int pulseCount = 0;  // Counter for the pulses
unsigned long lastTime = 0;  // Stores the last time RPM was calculated
unsigned int rpm = 0;  // Stores the calculated RPM
float distance = 0;
float distanceAnt = 0;
float speed = 0;
int runningTime = 0;

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

// Funciones de control para DE/RE
void preTransmission() {
  digitalWrite(pinEnable, HIGH);  // Activa transmisión
}

void postTransmission() {
  digitalWrite(pinEnable, LOW);  // Activa recepción
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(hallSensorPin, INPUT_PULLUP);  // KY-003 has an open-drain output, use internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), countPulse, FALLING);  // Interrupt on falling edge
}

void loop() {
  unsigned long currentTime = millis();

  // Calculate RPM every second (1000ms)
  if (currentTime - lastTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(hallSensorPin));  // Stop counting during calculation

    rpm = (pulseCount * 60 * 3.25);  // Convert pulse count to RPM (assuming 1 pulse per revolution)
    distance = distance + (pulseCount*1.54);
    speed = (distance - distanceAnt) * (3.6); 
    
    if (result == node.ku8MBSuccess) {
      unsigned long voltageLecture = (node.getResponseBuffer(0x00) << 16 | node.getResponseBuffer(0x01));
      unsigned long  currentLecture = (node.getResponseBuffer(0x02) << 16 | node.getResponseBuffer(0x03));
      //como el manual indica se utiliza unsigned long, para evitar errores de lectura cuando los valores son superiores a 65,535 se utiliza unsigned long (capaz de almacenar muchos más)
    }
  
    //Values reset
    distanceAnt = distance;
    pulseCount = 0;  // Reset pulse count
    lastTime = currentTime;  // Update time

    attachInterrupt(digitalPinToInterrupt(hallSensorPin), countPulse, FALLING);  // Re-enable interrupt
  }
}

// Interrupt service routine to count pulses
void countPulse() {
  pulseCount++;
}
