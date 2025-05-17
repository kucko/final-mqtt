#include <Arduino.h>
#include <WiFiS3.h>
#include <PubSubClient.h>

#include "domain/SensorReading.h"
#include "domain/TemperatureRange.h"
#include "application/DetectarAlertaUseCase.h"
#include "infrastructure/Max6675SensorAdapter.h"
#include "infrastructure/MQTTPublisherAdapter.h"

// Pines del sensor
#define PIN_SCK 7
#define PIN_CS 6
#define PIN_SO 5

// WiFi
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// MQTT
const char* mqttBroker = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "sensor/alerta";

// Objetos globales
WiFiClient net;
PubSubClient mqttClient(net);
Max6675SensorAdapter sensor(PIN_SCK, PIN_CS, PIN_SO);
TemperatureRange rango(15.0, 45.0);
MQTTPublisherAdapter mqttPublisher(&mqttClient, mqttTopic);
DetectarAlertaUseCase detectarAlerta(&rango, &mqttPublisher);

unsigned long lastMillis = 0;

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando a MQTT...");
    if (mqttClient.connect("arduino-sensor")) {
      Serial.println("conectado.");
    } else {
      Serial.print("error: ");
      Serial.println(mqttClient.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());

  mqttClient.setServer(mqttBroker, mqttPort);
  connectMQTT();
}

void loop() {
  mqttClient.loop();
  if (!mqttClient.connected()) connectMQTT();

  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

    SensorReading lectura;
    lectura.timestamp = millis();
    lectura.rawValue = sensor.readTemperature();
    lectura.calibratedValue = lectura.rawValue;
    lectura.isValid = !isnan(lectura.rawValue);

    Serial.print("Temp: ");
    Serial.println(lectura.calibratedValue);

    detectarAlerta.execute(lectura);
  }
}
