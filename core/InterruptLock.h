#ifndef INT_LOCK_H
#define INT_LOCK_H

#include <stdint.h>

struct ScopedInterruptLock {
  ScopedInterruptLock();
  ~ScopedInterruptLock();

 private:
  uint8_t SReg;
};

#endif