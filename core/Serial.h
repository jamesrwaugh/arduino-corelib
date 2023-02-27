#ifndef SERIAL_JWSQ_H
#define SERIAL_JWSQ_H

#include "Print.h"

const uint8_t BUFFER_SIZE2 = 16;

class JwSqSerial : public Print {
 public:
  void begin(uint32_t baudRate);
  uint8_t read();
  uint8_t available() const;
  virtual size_t write(uint8_t) override;
  void handle_rx_irq();

 private:
  uint8_t data_buffer[BUFFER_SIZE2];
  uint8_t write_pointer = 0;
  uint8_t read_pointer = 0;
};

extern JwSqSerial Serial;

#endif