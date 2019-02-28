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
  spi_comm.masterInit(10);

}

void loop() {
  String printOut = "";
  // Communication begin;
  digitalWrite(LEDPIN, HIGH);
  digitalWrite(spi_comm.CSPIN, LOW);
  delay(1000);
  spi_comm.transfer(str);
  delay(1000);
  digitalWrite(spi_comm.CSPIN, HIGH);
  digitalWrite(LEDPIN, LOW);
  // End of communication
  Serial.println(printOut);  
  delay(2000);
  
}
