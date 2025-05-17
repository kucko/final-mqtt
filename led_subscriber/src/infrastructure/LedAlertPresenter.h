#pragma once
#include <Arduino.h>
#include "../interfaces/AlertaPresenterPort.h"

class LedAlertPresenter : public AlertaPresenterPort {
private:
  int pin;

public:
  LedAlertPresenter(int p) : pin(p) {
    pinMode(pin, OUTPUT);
  }

  void mostrar(const Alerta& alerta) override {
    digitalWrite(pin, alerta.estaActiva() ? HIGH : LOW);
  }
};
