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
char buf[100];
volatile uint8_t pos;
volatile bool process_it;

void setup() {
  Serial.begin(9600);
  Serial.println("Program begin _ Slave:");
  // pinMode(LEDPIN,OUTPUT);
  // // initialize SPI Master:
  // spi_comm.slaveInit();
  // spi_comm.attachInterrupt();
  
}

void loop() {
  // char printOut;
  // // Communication begin;    

  // digitalWrite(LEDPIN, !digitalRead(LEDPIN));
  // if (process_it == true) {
  //   Serial.println(buf);  
  //   pos = 0;
  //   process_it = false;
  // }
  // delay(2000);
  
}

ISR (SPI_STC_vect)
{
  Serial.println("hello");
  uint8_t c = SPDR;
  Serial.println(char(c));
  if (pos< sizeof(buf)) {
    buf[pos++];
    if (c == '\n') process_it = true;
  }
}