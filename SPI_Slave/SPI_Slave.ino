/*
 * SPI Communication Master/Slave through SS pin 9
 * 
 */


// inslude the SPI library:
#include <SPI_COMM.h>


// set pin 10 as the slave select for the digital pot:
const int LEDPIN = 2;
const char str = 'A';
SPI_COMM spi_comm = SPI_COMM();

void setup() {
  Serial.begin(9600);
  Serial.println("Program begin:");
  pinMode(LEDPIN,OUTPUT);
  // initialize SPI Master:
  spi_comm.slaveInit();

}

void loop() {
  char printOut;
  // Communication begin;    

  digitalWrite(LEDPIN, !digitalRead(LEDPIN));

  printOut = char(spi_comm.transfer('B'));
  Serial.println(printOut);  
  delay(2000);
  
}