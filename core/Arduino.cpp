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
#include <util/delay.h>

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
  // uint8_t portNumber = 3;

  if (portNumber == INVALID_PIN || portNumber > 3) {
    IsValid = false;
    return;
  }

  // DDR = (volatile uint8_t*)(pgm_read_word(PortToDirectionMap + portNumber));
  // PORT = (volatile uint8_t*)(pgm_read_word(PortToPortMap + portNumber));
  // Number = pgm_read_byte(PinToPinNumberMap + portNumber);
  DDR = PortToDirectionMap[portNumber];
  PORT = PortToPortMap[portNumber];
  Number = PinToPinNumberMap[physicalPin];
  // DDR = &DDRD;
  // PORT = &PORTD;
  // Number = 7;

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

/*
40 PA0 (ADC0)
39 PA1 (ADC1)
38 PA2 (ADC2)
37 PA3 (ADC3)
36 PA4 (ADC4)
35 PA5 (ADC5)
34 PA6 (ADC6)
33 PA7 (ADC7)
*/

uint16_t analogRead(uint8_t pin) {
  // Enable ADC
  ADCSRA |= ((1 << ADEN));

  // Set reference: AVCC with external capacitor at AREF pin
  ADMUX &= ~(1 << REFS1);
  ADMUX |= (1 << REFS0);

  // Right adjust result
  ADMUX &= ~(1 << ADLAR);

  // Select pin setting lower MUX[4:0] bits
  ADMUX |= (0b00000 | (pin - 40));

  // Start convertsion
  ADCSRA |= (1 << ADSC);

  // Wait for conversion to finish
  while (ADCSRA & (1 << ADSC))
    ;

  uint16_t result = (ADCH << 8) | ADCL;

  return result;
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
