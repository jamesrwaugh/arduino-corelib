/*
  shiftOut() function
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/
#include "Arduino.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>

#include "wiring_private.h"

#define INVALID_PIN UINT8_MAX

volatile uint8_t* PortToDirectionMap[4] = {
    &DDRA,
    &DDRB,
    &DDRC,
    &DDRD,
};

volatile uint8_t* PortToPortMap[4] = {
    &PORTA,
    &PORTB,
    &PORTC,
    &PORTD,
};

volatile uint8_t* PortToPinMap[4] = {
    &PINA,
    &PINB,
    &PINC,
    &PIND,
};

uint8_t PinToPinNumberMap[41] = {
    /* 0  */ INVALID_PIN,
    // PORTB
    /* 1  */ 0,
    /* 2  */ 1,
    /* 3  */ 2,
    /* 4  */ 3,
    /* 5  */ 4,
    /* 6  */ 5,
    /* 7  */ 6,
    /* 8  */ 7,
    /* 9  */ INVALID_PIN,
    /* 10 */ INVALID_PIN,
    /* 11 */ INVALID_PIN,
    /* 12 */ INVALID_PIN,
    /* 13 */ INVALID_PIN,
    // PORT D
    /* 14 */ 0,
    /* 15 */ 1,
    /* 16 */ 2,
    /* 17 */ 3,
    /* 18 */ 4,
    /* 19 */ 5,
    /* 20 */ 6,
    /* 21 */ 7,
    // PORT C
    /* 22 */ 0,
    /* 23 */ 1,
    /* 24 */ 2,
    /* 25 */ 3,
    /* 26 */ 4,
    /* 27 */ 5,
    /* 28 */ 6,
    /* 29 */ 7,
    /* 30 */ INVALID_PIN,
    /* 31 */ INVALID_PIN,
    /* 32 */ INVALID_PIN,
    // PORT A
    /* 33 */ 0,
    /* 34 */ 1,
    /* 35 */ 2,
    /* 36 */ 3,
    /* 37 */ 4,
    /* 38 */ 5,
    /* 39 */ 6,
    /* 40 */ 7,
};

const uint8_t PinToPortMap[41] = {
    /* 0  */ INVALID_PIN,
    // PORTB
    /* 1  */ 1,
    /* 2  */ 1,
    /* 3  */ 1,
    /* 4  */ 1,
    /* 5  */ 1,
    /* 6  */ 1,
    /* 7  */ 1,
    /* 8  */ 1,
    /* 9  */ INVALID_PIN,
    /* 10 */ INVALID_PIN,
    /* 11 */ INVALID_PIN,
    /* 12 */ INVALID_PIN,
    /* 13 */ INVALID_PIN,
    // PORT D
    /* 14 */ 3,
    /* 15 */ 3,
    /* 16 */ 3,
    /* 17 */ 3,
    /* 18 */ 3,
    /* 19 */ 3,
    /* 20 */ 3,
    /* 21 */ 3,
    // PORT C
    /* 22 */ 2,
    /* 23 */ 2,
    /* 24 */ 2,
    /* 25 */ 2,
    /* 26 */ 2,
    /* 27 */ 2,
    /* 28 */ 2,
    /* 29 */ 2,
    /* 30 */ INVALID_PIN,
    /* 31 */ INVALID_PIN,
    /* 32 */ INVALID_PIN,
    // PORT A
    /* 33 */ 0,
    /* 34 */ 0,
    /* 35 */ 0,
    /* 36 */ 0,
    /* 37 */ 0,
    /* 38 */ 0,
    /* 39 */ 0,
    /* 40 */ 0,
};

struct PinMap {
  PinMap(uint8_t physicalPin);
  bool IsValid = false;
  volatile uint8_t* DDR = nullptr;
  volatile uint8_t* PORT = nullptr;
  volatile uint8_t* PIN = nullptr;
  uint8_t Number = 0;
};

PinMap::PinMap(uint8_t physicalPin) {
  if (physicalPin == 0 || physicalPin > 40) {
    IsValid = false;
    return;
  }

  uint8_t portNumber = PinToPortMap[physicalPin];

  if (portNumber == INVALID_PIN || portNumber > 3) {
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

struct ScopedInterruptLock {
  ScopedInterruptLock() {
    SReg = SREG;
    cli();
  }
  ~ScopedInterruptLock() { SREG = SReg; }

 private:
  uint8_t SReg;
};

void pinMode(uint8_t pin, uint8_t mode) {
  ScopedInterruptLock lock;
  PinMap Pin(pin);
  if (!Pin.IsValid) return;

  if (mode == OUTPUT) {
    *Pin.DDR |= (1 << Pin.Number);
  } else if (mode == INPUT) {
    *Pin.DDR &= ~(1 << Pin.Number);
    *Pin.PORT &= ~(1 << Pin.Number);
  } else if (mode == INPUT_PULLUP) {
    *Pin.DDR &= ~(1 << Pin.Number);
    *Pin.PORT |= (1 << Pin.Number);
  }
}

void digitalWrite(uint8_t pin, uint8_t value) {
  ScopedInterruptLock lock;
  PinMap Pin(pin);
  if (!Pin.IsValid) return;

  if (value) {
    *Pin.PORT |= (1 << Pin.Number);
  } else {
    *Pin.PORT &= ~(1 << Pin.Number);
  }
}

uint8_t digitalRead(uint8_t pin) {
  PinMap Pin(pin);
  if (!Pin.IsValid) return LOW;
  return (*Pin.PIN & (1 << Pin.Number)) ? HIGH : LOW;
}

uint8_t pinToAdcRef324p(uint8_t pin) {
  switch (pin) {
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
      return INVALID_PIN;
  }
}

uint16_t analogRead(uint8_t pin) {
  uint8_t ref = pinToAdcRef324p(pin);
  if (ref == INVALID_PIN) return 0;

  // REFS0: AVCC with external capacitor at AREF pin
  // Set reference: AVCC with external capacitor at AREF pin
  ADMUX &= ~(1 << REFS1);
  ADMUX |= (1 << REFS0);
  ADMUX |= (ref);

  // start the conversion
  sbi(ADCSRA, ADSC);

  // ADSC is cleared when the conversion finishes
  while (bit_is_set(ADCSRA, ADSC))
    ;

  // ADC macro takes care of reading ADC register.
  // avr-gcc implements the proper reading order: ADCL is read first.
  return ADC;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val) {
  uint8_t i;

  for (i = 0; i < 8; i++) {
    if (bitOrder == LSBFIRST) {
      digitalWrite(dataPin, val & 1);
      val >>= 1;
    } else {
      digitalWrite(dataPin, (val & 128) != 0);
      val <<= 1;
    }

    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
}
