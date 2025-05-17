// main.cpp para led_subscriber
#include <Arduino.h>
#include <WiFiS3.h>
#include <MQTT.h>

#include "application/ProcesarAlertaUseCase.h"
#include "infrastructure/LedAlertPresenter.h"

// WiFi
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// MQTT
const char* mqttBroker = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "sensor/alerta";

// Objetos globales
WiFiClient net;
MQTTClient mqttClient;
LedAlertPresenter led(8);
ProcesarAlertaUseCase procesador(&led);

void mensajeRecibido(String &topic, String &payload) {
  Serial.println("Mensaje recibido: " + payload);
  procesador.execute(payload);
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando a MQTT...");
    if (mqttClient.connect("arduino-receptor")) {
      Serial.println("Conectado.");
      mqttClient.subscribe(mqttTopic);
    } else {
      Serial.print("Error: ");
      Serial.println(mqttClient.lastError());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());

  mqttClient.begin(mqttBroker, mqttPort, net);
  mqttClient.onMessage(mensajeRecibido);
  connectMQTT();
}

void loop() {
  mqttClient.loop();
  if (!mqttClient.connected()) connectMQTT();
}
