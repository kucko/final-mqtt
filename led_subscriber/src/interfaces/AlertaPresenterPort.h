#pragma once
#include "../domain/Alerta.h"

class AlertaPresenterPort {
public:
  virtual ~AlertaPresenterPort() = default;
  virtual void mostrar(const Alerta& alerta) = 0;
}; 