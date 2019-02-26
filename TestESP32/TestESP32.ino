#include <Arduino.h>

const int LEDPIN = 16;
const int BUTTONPIN = 17;

int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  digitalWrite(LEDPIN, LOW);
  Serial.begin(115200);
  Serial.println(INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(BUTTONPIN);
  if(buttonState == LOW) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }
  delay(100);
}
