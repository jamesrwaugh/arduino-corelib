#include "Arduino.h"
#include "Serial.h"

int main() {
  init();

  Serial.begin(9600);

  pinMode(21, INPUT);

  while (1) {
    uint8_t value = digitalRead(21);
    Serial.println(value);
    delay(100);
  }
}
