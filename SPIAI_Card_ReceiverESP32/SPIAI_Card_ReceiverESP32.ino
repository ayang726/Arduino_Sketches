

/* The ESP32 has four SPi buses, however as of right now only two of
 * them are available to use, HSPI and VSPI. Simply using the SPI API 
 * as illustrated in Arduino examples will use VSPI, leaving HSPI unused.
 * 
 * However if we simply intialise two instance of the SPI class for both
 * of these buses both can be used. However when just using these the Arduino
 * way only will actually be outputting at a time.
 * 
 * Logic analyser capture is in the same folder as this example as
 * "multiple_bus_output.png"
 * 
 * created 30/04/2018 by Alistair Symonds
 */
#include <SPI.h>
#include <SPI_Helper.h>

static const int spiClk = 1000000; // 1 MHz

//uninitalised pointers to SPI objects
SPIClass * vspi = NULL;
SPIClass * hspi = NULL;

void setup() {
  Serial.begin(115200);
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);
  
  //clock miso mosi ss

  //initialise vspi with default pins
  //SCLK = 18, MISO = 19, MOSI = 23, SS = 5
  vspi->begin();
  //alternatively route through GPIO pins of your choice
  //hspi->begin(0, 2, 4, 33); //SCLK, MISO, MOSI, SS
  
  //initialise hspi with default pins
  //SCLK = 14, MISO = 12, MOSI = 13, SS = 15
  hspi->begin(); 
  //alternatively route through GPIO pins
  //hspi->begin(25, 26, 27, 32); //SCLK, MISO, MOSI, SS

  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
  pinMode(5, OUTPUT); //VSPI SS
  pinMode(15, OUTPUT); //HSPI SS

  Serial.println("Begin program, SPI Master, AICard Receiver");
  Serial.println(sizeof(float));

}
int i = 0;
// the loop function runs over and over again until power down or reset
void loop() {
  //use the SPI buses
  vspiCommand();
  
//  hspiCommand();
  delay(3000);
}
//////////////////NEW LIBRARY////////////////////////
float dataTable[16];
int sizeOfDataTable = 16;
float *dataPtr {dataTable};

void clearDataTable() {
    for(size_t i = 0; i < sizeOfDataTable; i++)
    {
        dataTable[i] = 0x0000;
    }
}
void printDataTable() {
    resetPtr();
    Serial.println("Printing dataTable values");
    for(size_t i = 0; i < sizeOfDataTable / 4; i++)
    {   
        Serial.print("Device #");
        Serial.println(i);
        
        for(size_t j = 0; j < 4; j++)
        {
            Serial.print(*dataPtr++,4);
            Serial.print(" ");
        }   
        Serial.println();
    }
    resetPtr();   
}

void resetPtr() {
    dataPtr = dataTable;
}

////////////////////////////////////////////////////
void vspiCommand() {
  //use it as you would the regular arduino SPI API
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
///////////////////////TEST CODE////////////////////////////////////
  Serial.println("Data Received");
  spiReceive(vspi, dataTable, sizeOfDataTable);
  printDataTable();
////////////////////////////////////////////////////////////////////
//  Serial.println(vspi->transfer(data));  
  digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();
}
void hspiCommand() {
  byte stuff = 0b11001100;
  
  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(15, LOW);
  hspi->transfer(stuff);
  digitalWrite(15, HIGH);
  hspi->endTransaction();
}
