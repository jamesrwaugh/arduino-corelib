#include "Arduino.h"
#include "Serial.h"

int main() {
  init();

  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  while (1) {
    // Serial.println("Hello World!");
    digitalWrite(14, HIGH);
    delay(1000);

    digitalWrite(14, LOW);
    delay(1000);
  }
}
