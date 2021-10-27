#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WiFiClient client;
ESP8266WebServer server(80);

/* Define WiFi Credentials */
const char *ssid = "ESP-APUYSTEREO";
const char *password = "12345678QWERTY";

String direction = "";
int speed = 100;
int speedManuver = 85;

#define IN1 D2
#define IN2 D3
#define IN3 D7
#define IN4 D8
#define ENA D5
#define ENB D6

void handleRequest()
{
  if (server.hasArg("direction"))
  {
    Serial.println(server.arg("direction"));
  }
  server.send(200, "text/html", "");
  delay(1);
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void left()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedManuver);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedManuver);
}

void right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedManuver);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedManuver);
}

void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("APUYSTEREO new test!");
  //initial motor
  pinMode(D4, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  /* create server WiFi */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP.toString());
  server.on("/", handleRequest);
  server.onNotFound(handleRequest);
  /* Starting Server */
  server.begin();
  Serial.println("Server started");
}

void loop()
{
  /* Handling Request */
  server.handleClient();
  String direction = server.arg("direction");
  Serial.println(direction);
  digitalWrite(D4, HIGH);
  digitalWrite(D4, LOW);
  if (direction == "F")
  {
    forward();
  }
  else if (direction == "B")
  {
    backward();
  }
  else if (direction == "L")
  {
    left();
  }
  else if (direction == "R")
  {
    right();
  }
  else if (direction == "S")
  {
    stop();
  }
}
