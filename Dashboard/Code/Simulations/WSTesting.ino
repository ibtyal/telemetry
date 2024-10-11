#include <WiFi.h>
#include <ArduinoWebsockets.h>
//Global variables
// Pins declaration
#define potPin 33
#define sessionButton 12 
#define LED_PIN 27

int timeReset= 0;
int potMapped;

float potValue;
int runningTime = 0;
float distanceTot = 0;
bool capturing = false;

//WS configuration
const char* websockets_server = "wss://echo.websocket.org"; //server adress and port
using namespace websockets;
WebsocketsClient client;

void sendData (float voltage, float current, float rpm, float distance, float velocity) {
runningTime++; // increases one second the running time
distanceTot += distance;
String telemetry = "{\"Time(sec)\": " + String(runningTime) + ", \"Voltage\": " + String(voltage) + ", \"Current\": " + String(current) + ", \"RPM\": " + String(rpm) + ", \"Distance\":" + String(distanceTot) + ", \"Velocity\":" + String(velocity) + "}"; 
Serial.println(telemetry);
client.send(telemetry);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(sessionButton, INPUT_PULLUP);
  //Setting up WiFi connection
  Serial.begin(115200);
  Serial.println("Welcome to SIIMA telemetry project");
  Serial.println("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
 Serial.println("Connected to Wifi, Connecting to server.");
 client.connect(websockets_server);
 delay(10000);
  //client.connect(websockets_server);
  Serial.println("WebSocket connected");
  Serial.println("Press the red button to initiate sesion");
}



void loop() {
  //Sending Data by default
  if (digitalRead(sessionButton) == LOW){
    delay(50);
    capturing = !capturing;
  }
  if (capturing == true) {
    potValue = analogRead(potPin); //reads potentiometter value
    potMapped = map(potValue, 0, 4094, 0, 100);  //converts or maps potentiometer value to into a value between 0 to 100
    sendData ((39 + 0.09*potMapped), potMapped*0.208, potMapped*35, (potMapped*600/3600), potMapped*0.6);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(1000);
  }  

}