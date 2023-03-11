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

#include "chips/pinmap.h"
#include "wiring_private.h"

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

uint16_t analogRead(uint8_t pin) {
  uint8_t ref = pinToAdcReference(pin);
  if (ref == INVALID_ADC_REF) return 0;

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
