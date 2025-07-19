#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// --- Pins ---
#define ENA   14
#define ENB   12
#define IN_1  15
#define IN_2  13
#define IN_3  2
#define IN_4  0
#define TRIG_PIN 5
#define ECHO_PIN 4
#define MIC_PIN A0
#define DFPLAYER_RX D6  // You can change as needed
#define DFPLAYER_TX D5

// --- WiFi Credentials ---
const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";

// --- Objects ---
SoftwareSerial dfplayerSerial(DFPLAYER_RX, DFPLAYER_TX);
DFRobotDFPlayerMini mp3;
ESP8266WebServer server(80);

String command;
int speedCar = 800;
int micValue = 0;
const int MIC_THRESHOLD = 600;
long duration;
float distance;

void setup() {
  Serial.begin(115200);
  dfplayerSerial.begin(9600);

  if (!mp3.begin(dfplayerSerial)) {
    Serial.println("DFPlayer Mini not found");
    while (true);
  }

  mp3.volume(20);
  mp3.play(1); // Welcome

  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT); pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT); pinMode(IN_4, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  pinMode(MIC_PIN, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
  checkVoiceCommand();
  checkObstacles();
}

void goAhead() {
  digitalWrite(IN_1, LOW); digitalWrite(IN_2, HIGH); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW); digitalWrite(IN_4, HIGH); analogWrite(ENB, speedCar);
  mp3.play(2);
}

void goBack() {
  digitalWrite(IN_1, HIGH); digitalWrite(IN_2, LOW); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, HIGH); digitalWrite(IN_4, LOW); analogWrite(ENB, speedCar);
  mp3.play(3);
}

void goRight() {
  digitalWrite(IN_1, HIGH); digitalWrite(IN_2, LOW); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW); digitalWrite(IN_4, HIGH); analogWrite(ENB, speedCar);
  mp3.play(4);
}

void goLeft() {
  digitalWrite(IN_1, LOW); digitalWrite(IN_2, HIGH); analogWrite(ENA, speedCar);
  digitalWrite(IN_3, HIGH); digitalWrite(IN_4, LOW); analogWrite(ENB, speedCar);
  mp3.play(5);
}

void stopRobot() {
  digitalWrite(IN_1, LOW); digitalWrite(IN_2, LOW); analogWrite(ENA, 0);
  digitalWrite(IN_3, LOW); digitalWrite(IN_4, LOW); analogWrite(ENB, 0);
  mp3.play(6);
}

void checkObstacles() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10); digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  if (distance < 20 && distance > 0) {
    stopRobot();
    mp3.play(7);
    delay(2000);
  }
}

void checkVoiceCommand() {
  micValue = analogRead(MIC_PIN);
  if (micValue > MIC_THRESHOLD) {
    int pattern = map(micValue, MIC_THRESHOLD, 1023, 1, 5);
    switch (pattern) {
      case 1: command = "F"; mp3.play(8); break;
      case 2: command = "B"; mp3.play(9); break;
      case 3: command = "L"; mp3.play(10); break;
      case 4: command = "R"; mp3.play(11); break;
      case 5: command = "S"; mp3.play(12); break;
    }
    executeCommand();
    delay(2000);
  }
}

void playTtsResponse(String text) {
  if (text.indexOf("weather") >= 0) mp3.play(13);
  else if (text.indexOf("time") >= 0) mp3.play(14);
  else mp3.play(15);
}

void executeCommand() {
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "S") stopRobot();
}

void HTTP_handleRoot() {
  if (server.hasArg("State")) {
    command = server.arg("State");
    executeCommand();
  }
  server.send(200, "text/html", "Command Executed");
}
