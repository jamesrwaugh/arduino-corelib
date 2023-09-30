#ifndef CHIP_H
#define CHIP_H

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega168PA__)
#define HAVE_ATMEGA168 1
#elif defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324A__) ||                               \
    defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644A__) || \
    defined(__AVR_ATmega644PA__)
#define HAVE_ATMEGAXX4 1
#endif

#endif