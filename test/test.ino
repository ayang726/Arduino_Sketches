/*
 * SPI Communication Master/Slave through SS pin 9
 * 
 */


// inslude the SPI library:
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int LEDPIN = 2;
const int CSPIN = 9;
const int SSPIN = 10;
const int anotherPIN = 8;
const int DD_MOSI = DDB3;
const int DD_MISO = DDB4;
const int DD_SCK = DDB5;
const int PIN_MOSI = 11;
const int PIN_MISO = 12;
const int PIN_SCK = 13;
const char str = "A";

void setup() {
  Serial.begin(9600);
  Serial.println("Program begin:");
  
  pinMode(LEDPIN,OUTPUT);
  // initialize SPI Master:
  SPIMasterBegin();

}

void loop() {
  String printOut = "";
  
  // Communication begin;
  digitalWrite(LEDPIN, HIGH);
  digitalWrite(CSPIN, LOW);
  delay(10);
  Serial.println(digitalRead(CSPIN));
  Serial.println(digitalRead(anotherPIN));
  delay(1000);
//  transmit(str);
  delay(1000);
  digitalWrite(CSPIN, HIGH);
  Serial.println(digitalRead(CSPIN));
  Serial.println(digitalRead(anotherPIN));
  digitalWrite(LEDPIN, LOW);
  // End of communication
  Serial.println(printOut);  
  delay(2000);
  
}

void SPIMasterBegin()  {
  pinMode(SSPIN,OUTPUT);
  digitalWrite(SSPIN,HIGH);
  pinMode(CSPIN,OUTPUT);
  digitalWrite(CSPIN, HIGH);
  Serial.println(digitalRead(CSPIN));
  Serial.println(digitalRead(anotherPIN));
    digitalWrite(CSPIN, LOW);
  Serial.println(digitalRead(CSPIN));
  Serial.println(digitalRead(anotherPIN));
    digitalWrite(CSPIN, HIGH);
  Serial.println(digitalRead(CSPIN));
  Serial.println(digitalRead(anotherPIN));
    digitalWrite(CSPIN, LOW);
  Serial.println(digitalRead(CSPIN));
  Serial.println(digitalRead(anotherPIN));
  pinMode(anotherPIN, INPUT);
//  pinMode(CSPIN, INPUT);
//  digitalWrite(CSPIN, HIGH);
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_SCK, OUTPUT);

//  DDRB = (1<<DD_MOSI)|(1<<DD_SCK);
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
  
}

void SPISlaveBegin() {
  pinMode(SSPIN, INPUT);
  pinMode(PIN_MISO, OUTPUT);
  DDRB = (1<<DD_MISO);
  SPCR = (1<<SPE);
}

char transceive(char data){
  SPDR = data;
  while(!(SPSR & (1 << SPIF))){
    Serial.println("transmitting Data");
  }
  return SPDR;
}

void transmit(char data) {
  SPDR = data;
  while(!(SPSR & (1 << SPIF))){Serial.println(digitalRead(SSPIN));};
}

char receive() {
    while(!(SPSR & (1 << SPIF)));
    return SPDR;
}
