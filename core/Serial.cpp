#include "Serial.h"

#include <avr/interrupt.h>
#include <avr/io.h>

void JwSqSerial::begin(uint32_t baudRate) {
  // 2X rates - need U2X0 set
  uint16_t baud_setting_2x = (F_CPU / 4 / baudRate - 1) / 2;

  // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
  UBRR0H = baud_setting_2x >> 8;
  UBRR0L = baud_setting_2x;

  UCSR0A |= (1 << U2X0);
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  UCSR0B |= (1 << RXCIE0);
}

uint8_t JwSqSerial::read() {
  uint8_t item = data_buffer[read_pointer++];
  read_pointer %= BUFFER_SIZE2;
  return item;
}

uint8_t JwSqSerial::available() const {
  return ((unsigned int)(BUFFER_SIZE2 + write_pointer - read_pointer)) % BUFFER_SIZE2;
}

size_t JwSqSerial::write(uint8_t data) {
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  // Put data into buffer, sends the data
  UDR0 = data;
  return 1;  // 1 for 1 byte written; assume sucess
}

void JwSqSerial::handle_rx_irq() {
  if (bit_is_clear(UCSR0A, DOR0) && bit_is_clear(UCSR0A, FE0)) {
    uint8_t data = UDR0;
    uint8_t next_write_slot = (write_pointer + 1) % BUFFER_SIZE2;
    if (next_write_slot != read_pointer) {
      data_buffer[write_pointer] = data;
      write_pointer = next_write_slot;
    }
  } else {
    uint8_t _ = UDR0;
  }
}

JwSqSerial Serial;

ISR(USART0_RX_vect) { Serial.handle_rx_irq(); }