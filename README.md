Implements the Arduino APIs such as `digitalRead`, `analogRead`, `Serial` and more for general-purpose AVRs.

Some code is directly from the official Arduino core, others is reimplemented.

Note that this is slimmed down to my specific purposes, such as no floating points, no `String` and other space-saving measures.

## How To Compile

- Have `avr-gcc` on your path with the standard `avr libc` headers available
- Edit Makefile if needed; change clock speed or device
- run `make`
