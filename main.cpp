#include "Arduino.h"
#include "Serial.h"

int main() {
  init();

  Serial.begin(9600);

  pinMode(21, OUTPUT);
  digitalWrite(21, LOW);

  while (1) {
    uint16_t value = analogRead(34);
    Serial.println(value);
    delay(100);
  }
}
