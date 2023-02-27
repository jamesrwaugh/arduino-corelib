#include "Arduino.h"
#include "Serial.h"

int main() {
  init();

  Serial.begin(9600);

  while (1) {
    if (Serial.available()) {
      char data = Serial.read();
      Serial.print("Got: ");
      Serial.println(data);
    }
  }
}
