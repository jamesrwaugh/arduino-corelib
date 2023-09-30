#ifndef ATMEGA168_PINS_H
#define ATMEGA168_PINS_H

#include "chip.h"

#ifdef HAVE_ATMEGA168

#include <avr/interrupt.h>
#include <avr/io.h>

#define INVALID_PIN 255
#define TOTAL_PIN_COUNT 28
#define NUMBER_OF_PORTS 3

volatile uint8_t* PortToDirectionMap[NUMBER_OF_PORTS] = {
    &DDRB,
    &DDRC,
    &DDRD,
};

volatile uint8_t* PortToPortMap[NUMBER_OF_PORTS] = {
    &PORTB,
    &PORTC,
    &PORTD,
};

volatile uint8_t* PortToPinMap[NUMBER_OF_PORTS] = {
    &PINB,
    &PINC,
    &PIND,
};

uint8_t PinToPinNumberMap[TOTAL_PIN_COUNT + 1] = {
    /* 0  */ INVALID_PIN,
    // PORT C
    /* 1  */ 6,
    // PORT D
    /* 2  */ 0,
    /* 3  */ 1,
    /* 4  */ 2,
    /* 5  */ 3,
    /* 6  */ 4,
    /* 7  */ INVALID_PIN,
    /* 8  */ INVALID_PIN,
    // PORT B
    /* 9  */ 6,
    /* 10 */ 7,
    // PORT D
    /* 11 */ 5,
    /* 12 */ 6,
    /* 13 */ 7,
    // PORT B
    /* 14 */ 0,
    /* 15 */ 1,
    /* 16 */ 2,
    /* 17 */ 3,
    /* 18 */ 4,
    /* 19 */ 5,
    /* 20 */ INVALID_PIN,
    /* 21 */ INVALID_PIN,
    /* 22 */ INVALID_PIN,
    // PORT C
    /* 23 */ 0,
    /* 24 */ 1,
    /* 25 */ 2,
    /* 26 */ 3,
    /* 27 */ 4,
    /* 28 */ 5,
};

const uint8_t PinToPortMap[TOTAL_PIN_COUNT + 1] = {
    /* 0  */ INVALID_PIN,
    // PORT C
    /* 1  */ 1,
    // PORT D
    /* 2  */ 2,
    /* 3  */ 2,
    /* 4  */ 2,
    /* 5  */ 2,
    /* 6  */ 2,
    /* 7  */ INVALID_PIN,
    /* 8  */ INVALID_PIN,
    // PORT B
    /* 9  */ 0,
    /* 10 */ 0,
    // PORT D
    /* 11 */ 2,
    /* 12 */ 2,
    /* 13 */ 2,
    // PORT B
    /* 14 */ 0,
    /* 15 */ 0,
    /* 16 */ 0,
    /* 17 */ 0,
    /* 18 */ 0,
    /* 19 */ 0,
    /* 20 */ INVALID_PIN,
    /* 21 */ INVALID_PIN,
    /* 22 */ INVALID_PIN,
    // PORT C
    /* 23 */ 1,
    /* 24 */ 1,
    /* 25 */ 1,
    /* 26 */ 1,
    /* 27 */ 1,
    /* 28 */ 1,
};

#endif

#endif