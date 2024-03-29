#include "pinmap.h"

#include "chip.h"

#ifdef HAVE_ATMEGA168
#include "atmega168.h"
#elif HAVE_ATMEGAXX4
#include "atmegaxx4.h"
#endif

PinMap::PinMap(uint8_t physicalPin) {
  if (physicalPin == 0 || physicalPin > TOTAL_PIN_COUNT) {
    IsValid = false;
    return;
  }

  uint8_t portNumber = PinToPortMap[physicalPin];

  if (portNumber == INVALID_PIN || portNumber > NUMBER_OF_PORTS) {
    IsValid = false;
    return;
  }

  DDR = PortToDirectionMap[portNumber];
  PORT = PortToPortMap[portNumber];
  PIN = PortToPinMap[portNumber];
  Number = PinToPinNumberMap[physicalPin];

  if (Number == INVALID_PIN) {
    IsValid = false;
    return;
  }

  IsValid = true;
}

uint8_t pinToAdcReference(uint8_t physicalPin) {
#ifdef HAVE_ATMEGA168
  switch (physicalPin) {
    case 23:
      return 0;
    case 24:
      return 1;
    case 25:
      return 2;
    case 26:
      return 3;
    case 27:
      return 4;
    case 28:
      return 5;
    default:
      return INVALID_ADC_REF;
  }
#elif HAVE_ATMEGAXX4
  switch (physicalPin) {
    case 40:
      return 0;
    case 39:
      return 1;
    case 38:
      return 2;
    case 37:
      return 3;
    case 36:
      return 4;
    case 35:
      return 5;
    case 34:
      return 6;
    case 33:
      return 7;
    default:
      return INVALID_ADC_REF;
  }
#else
#error Compiling for unsupported AVR
#endif
}

uint8_t digitalPinToPort(uint8_t ss) { return PinToPortMap[ss]; }

uint8_t digitalPinToBitMask(uint8_t ss) { return PinToPinNumberMap[ss]; }

volatile uint8_t* portModeRegister(uint8_t port) { return PortToDirectionMap[port]; }