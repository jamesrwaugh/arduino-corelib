/*
 Stream.cpp - adds parsing methods to Stream class
 Copyright (c) 2008 David A. Mellis.  All right reserved.

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

 Created July 2011
 parsing functions based on TextFinder library by Michael Margolis

 findMulti/findUntil routines written by Jim Leonard/Xuth
 */

#include "Stream.h"

#include "Arduino.h"

#define PARSE_TIMEOUT 1000  // default number of milli-seconds to wait

// protected method to read stream with timeout
int Stream::timedRead() {
  int c;
  _startMillis = millis();
  do {
    c = read();
    if (c >= 0) return c;
  } while (millis() - _startMillis < _timeout);
  return -1;  // -1 indicates timeout
}

// protected method to peek stream with timeout
int Stream::timedPeek() {
  int c;
  _startMillis = millis();
  do {
    c = peek();
    if (c >= 0) return c;
  } while (millis() - _startMillis < _timeout);
  return -1;  // -1 indicates timeout
}

// Public Methods
//////////////////////////////////////////////////////////////

void Stream::setTimeout(unsigned long timeout)  // sets the maximum number of milliseconds to wait
{
  _timeout = timeout;
}

// read characters from stream into buffer
// terminates if length characters have been read, or timeout (see setTimeout)
// returns the number of characters placed in the buffer
// the buffer is NOT null terminated.
//
size_t Stream::readBytes(char *buffer, size_t length) {
  size_t count = 0;
  while (count < length) {
    int c = timedRead();
    if (c < 0) break;
    *buffer++ = (char)c;
    count++;
  }
  return count;
}
