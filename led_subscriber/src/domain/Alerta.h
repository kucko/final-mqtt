#pragma once
#include <Arduino.h>

class Alerta {
private:
  bool activa;

public:
  Alerta(bool estado) : activa(estado) {}

  bool estaActiva() const {
    return activa;
  }

  static Alerta desdePayload(const String& payload) {
    return Alerta(payload == "1");
  }
};
