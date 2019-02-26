#include <AI_BLOCK.h>
#include <ADS1115_COMM.h>

ADS1115_COMM ads = ADS1115_COMM();

AI_BLOCK ai1 = AI_BLOCK(&ads, 0, 0);

void setup() {
  Serial.begin(9600);
  ads.setup();
  ai1.setup();
  ai1.setXdScale(4,20);
  ai1.setOutScale(0,100);
}

void loop() {
  // put your main code here, to run repeatedly:
  ads.loop();
  ai1.loop();
  // Serial.print("Scanned value = ");
  // Serial.println(ai1.getFieldVal(),4);
  Serial.print("Output value = ");
  Serial.println(ai1.getOut(),2);

  delay(500);
}
