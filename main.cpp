#include "Arduino.h"
#include "Serial.h"

int main() {
  init();
  while (1) {
    Serial.println("Hello World!");
    digitalWrite(15, HIGH);
    digitalWrite(14, HIGH);
    delay(1000);
  }
}
