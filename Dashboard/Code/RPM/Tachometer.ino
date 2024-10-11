// Pin definitions
const int hallSensorPin = 2;  // KY-003 signal pin (S)
volatile unsigned int pulseCount = 0;  // Counter for the pulses
unsigned long lastTime = 0;  // Stores the last time RPM was calculated
unsigned int rpm = 0;  // Stores the calculated RPM
float distance = 0;
float distanceAnt = 0;
float speed = 0;

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
    
    Serial.print("RPM: ");
    Serial.print(rpm);
    Serial.print(" - Distancia: ");
    Serial.print(distance);
    Serial.print(", Velocidad - ");
    Serial.println(speed);
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
