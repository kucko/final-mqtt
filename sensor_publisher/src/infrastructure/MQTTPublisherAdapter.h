#pragma once
#include <PubSubClient.h>
#include "../interfaces/AlertaPublisherPort.h"

class MQTTPublisherAdapter : public AlertaPublisherPort {
private:
  PubSubClient* client;
  const char* topic;

public:
  MQTTPublisherAdapter(PubSubClient* mqttClient, const char* mqttTopic)
    : client(mqttClient), topic(mqttTopic) {}

  void publicarAlerta(const char* mensaje) override {
    client->publish(topic, mensaje);
  }
};
