// Inclusao das bibliotecas
#include <Arduino.h>
#include <OneWire.h>
#include <Wire.h>
#include <WiFi.h>
#include <ThingsBoard.h>
#include <ArduinoHttpClient.h>
#include <Update.h>
#include <Arduino_MQTT_Client.h>
#include "accelerometer.h"
#include "FS.h"
#define LED_BUILTIN_PORT13 2

// Insert your network credentials
#define WIFI_AP "CINGUESTS"
#define WIFI_PASS "acessocin"

#define TB_SERVER "mqtt.thingsboard.cloud"
#define TOKEN "v9wqm0zuxpytib00uz1x"

const int PINO_ONEWIRE = 4; // Define pino do sensor
OneWire oneWire(PINO_ONEWIRE); // Cria um objeto OneWire

constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;

WiFiClient espClient;

Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_AP, WIFI_PASS);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200); // Inicia a porta serial
  pinMode(LED_BUILTIN_PORT13, OUTPUT);

  Wire.begin();
  
  buildAccelerometer();
}
  
void loop() {
  if (WiFi.status() != WL_CONNECTED) initWiFi();

  delay(10);

  if (!tb.connected()) {
    Serial.println("Conectando ao servidor...");
    if (!tb.connect(TB_SERVER, TOKEN)) {
      Serial.println("Não foi possivel conectar");
      digitalWrite(LED_BUILTIN_PORT13, LOW);
      return;
    }
  } else {
    digitalWrite(LED_BUILTIN_PORT13, HIGH);
  }

  tb.sendTelemetryData("accel X: ", getAxisX());
  tb.sendTelemetryData("accel Y: ", getAxisY());
  tb.sendTelemetryData("accel Z: ", getAxisZ());

  delay(1000);

  tb.loop();

  delay(1000);
}

//curl -v -X POST http://thingsboard.cloud/api/v1/v9wqm0zuxpytib00uz1x/telemetry --header Content-Type:application/json --data "{temperature:25}"