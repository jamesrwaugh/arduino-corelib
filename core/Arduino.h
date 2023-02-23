#ifndef ARDUINO_JWSQ_H
#define ARDUINO_JWSQ_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t boolean;
typedef uint8_t byte;

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

enum PinValue {
  LOW = 0,
  HIGH = 1,
};

enum ShiftBitOrder { LSBFIRST = 0, MSBFIRST = 1 };

void pinMode(uint8_t pin, uint8_t mode);
void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);
void digitalWrite(uint8_t pin, uint8_t value);
uint8_t digitalRead(uint8_t pin);
uint16_t analogRead(uint8_t pin);
unsigned long millis(void);
unsigned long micros(void);
void yield(void);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
void init(void);

#ifdef __cplusplus
}
#endif

#endif