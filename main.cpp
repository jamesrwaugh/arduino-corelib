#include "Arduino.h"
#include "Serial.h"

int main() {
  init();

  Serial.begin(9600);

  pinMode(21, OUTPUT);
  digitalWrite(21, LOW);

  while (1) {
    Serial.println("Hello World!");
    digitalWrite(21, HIGH);
    delay(500);

    digitalWrite(21, LOW);
    delay(500);
  }
}
