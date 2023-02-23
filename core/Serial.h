#ifndef SERIAL_JWSQ_H
#define SERIAL_JWSQ_H

#include "Print.h"

class JwSqSerial : public Print {
 public:
  void begin(uint32_t baudRate);
  virtual size_t write(uint8_t) override;
};

extern JwSqSerial Serial;

#endif