#include <AI_BLOCK.h>

int pin_in = A0;

AI_BLOCK ai1 = AI_BLOCK(pin_in);

void setup() {
  Serial.begin(9600);
  ai1.setup();
  ai1.setXdScale(0,1023);
  ai1.setOutScale(0,5);
}

void loop() {
  // put your main code here, to run repeatedly:
  ai1.loop();
  Serial.println(ai1.getOut(),6);
  Serial.print("Scanned value = ");
  Serial.println(ai1.getFieldVal(),4);
  delay(200);
}
