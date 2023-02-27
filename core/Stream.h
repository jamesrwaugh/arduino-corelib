/*
  Stream.h - base class for character-based streams.
  Copyright (c) 2010 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  parsing functions based on TextFinder library by Michael Margolis
*/

#ifndef Stream_h
#define Stream_h

#include <inttypes.h>

#include "Print.h"

// compatibility macros for testing
/*
#define   getInt()            parseInt()
#define   getInt(ignore)    parseInt(ignore)
#define   getFloat()          parseFloat()
#define   getFloat(ignore)  parseFloat(ignore)
#define   getString( pre_string, post_string, buffer, length)
readBytesBetween( pre_string, terminator, buffer, length)
*/

// This enumeration provides the lookahead options for parseInt(), parseFloat()
// The rules set out here are used until either the first valid character is found
// or a time out occurs due to lack of input.
enum LookaheadMode {
  SKIP_ALL,        // All invalid characters are ignored.
  SKIP_NONE,       // Nothing is skipped, and the stream is not touched unless the first waiting
                   // character is valid.
  SKIP_WHITESPACE  // Only tabs, spaces, line feeds & carriage returns are skipped.
};

#define NO_IGNORE_CHAR '\x01'  // a char not found in a valid ASCII numeric field

class Stream : public Print {
 protected:
  unsigned long
      _timeout;  // number of milliseconds to wait for the next char before aborting timed read
  unsigned long _startMillis;  // used for timeout measurement
  int timedRead();             // read stream with timeout
  int timedPeek();             // peek stream with timeout
  int peekNextDigit(
      LookaheadMode lookahead,
      bool detectDecimal);  // returns the next numeric digit in the stream or -1 if timeout

 public:
  virtual int available() = 0;
  virtual int read() = 0;
  virtual int peek() = 0;

  Stream() { _timeout = 1000; }

  // parsing methods

  void setTimeout(unsigned long timeout);  // sets maximum milliseconds to wait for stream data,
                                           // default is 1 second
  unsigned long getTimeout(void) { return _timeout; }

  size_t readBytes(char *buffer, size_t length);  // read chars from stream into buffer
  size_t readBytes(uint8_t *buffer, size_t length) { return readBytes((char *)buffer, length); }
};

#undef NO_IGNORE_CHAR
#endif
