void setup() {
  // put your setup code here, to run once:
  long num = 0;
  num = 129|110<<8|128<<16|91<<24;
  Serial.begin(115200);
  Serial.println(num);
  Serial.println(sizeof(long));
}

void loop() {
  // put your main code here, to run repeatedly:

}
