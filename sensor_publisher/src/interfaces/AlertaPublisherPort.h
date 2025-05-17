#pragma once

class AlertaPublisherPort {
public:
  virtual ~AlertaPublisherPort() = default;
  virtual void publicarAlerta(const char* estado) = 0;
};
