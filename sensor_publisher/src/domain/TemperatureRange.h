#pragma once

class TemperatureRange {
private:
  float minTemp;
  float maxTemp;

public:
  TemperatureRange(float min, float max) : minTemp(min), maxTemp(max) {}

  bool isOutOfRange(float value) const {
    return value < minTemp || value > maxTemp;
  }

  void set(float min, float max) {
    minTemp = min;
    maxTemp = max;
  }
};
