#ifndef ATMEGAXX4P_PINS_H
#define ATMEGAXX4P_PINS_H

#include "chip.h"
#ifdef HAVE_ATMEGAXX4

#include <avr/interrupt.h>
#include <avr/io.h>

#define INVALID_PIN 255
#define TOTAL_PIN_COUNT 40
#define NUMBER_OF_PORTS 4

volatile uint8_t* PortToDirectionMap[NUMBER_OF_PORTS] = {
    &DDRA,
    &DDRB,
    &DDRC,
    &DDRD,
};

volatile uint8_t* PortToPortMap[NUMBER_OF_PORTS] = {
    &PORTA,
    &PORTB,
    &PORTC,
    &PORTD,
};

volatile uint8_t* PortToPinMap[NUMBER_OF_PORTS] = {
    &PINA,
    &PINB,
    &PINC,
    &PIND,
};

uint8_t PinToPinNumberMap[TOTAL_PIN_COUNT + 1] = {
    /* 0  */ INVALID_PIN,
    // PORT B
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
    /* 33 */ 7,
    /* 34 */ 6,
    /* 35 */ 5,
    /* 36 */ 4,
    /* 37 */ 3,
    /* 38 */ 2,
    /* 39 */ 1,
    /* 40 */ 0,
};

const uint8_t PinToPortMap[TOTAL_PIN_COUNT + 1] = {
    /* 0  */ INVALID_PIN,
    // PORT B
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

#endif

#endif