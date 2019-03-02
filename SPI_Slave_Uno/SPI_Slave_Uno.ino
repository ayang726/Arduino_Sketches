#include <SPI_COMM.h>
#include <SPI_Helper.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Program Begin, Uno SPI Slave");
  spi.slaveInit();
  // spi.attachInterrupt();
}


void loop() {

  uint16_t data16[] {3215,48562,1235,200,6542} ; // junk data to illustrate usage
  uint8_t data8[] {15,62,123,200,2} ; // junk data to illustrate usage
  uint32_t data32[] {1535143553,3654311362,1224135433,2434531430,3543514312} ;
  spiTransmit(&spi, data16, 5);

}

// ISR(SPI_STC_vect) {
//   Serial.println("interrupt triggered");
//   uint8_t c = SPDR;
//   Serial.println(c);
//   buf[pos++] = c;
//   if (c == '\n') process_it = true;
// }
