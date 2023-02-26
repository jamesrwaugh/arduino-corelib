#include "Serial.h"

#include <avr/io.h>

void JwSqSerial::begin(uint32_t baudRate) {
  // 2X rates - need U2X0 set
  uint16_t baud_setting_2x = (F_CPU / 4 / baudRate - 1) / 2;

  // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
  UBRR0H = baud_setting_2x >> 8;
  UBRR0L = baud_setting_2x;

  UCSR0A |= (1 << U2X0);
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

size_t JwSqSerial::write(uint8_t data) {
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  // Put data into buffer, sends the data
  UDR0 = data;
  return 1;  // 1 for 1 byte written; assume sucess
}

JwSqSerial Serial;