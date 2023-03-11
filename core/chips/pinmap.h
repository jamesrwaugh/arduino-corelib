#ifndef PINMAP_H
#define PINMAP_H

#include <stdint.h>

struct PinMap {
  PinMap(uint8_t physicalPin);
  bool IsValid = false;
  volatile uint8_t* DDR = nullptr;
  volatile uint8_t* PORT = nullptr;
  volatile uint8_t* PIN = nullptr;
  uint8_t Number = 0;
};

#define INVALID_ADC_REF 255
uint8_t pinToAdcReference(uint8_t physicalPin);

#endif