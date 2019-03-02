#include <SPI_COMM.h>
#include <SPI_Helper.h>
#include <ADS1115_COMM.h>

ADS1115_COMM ads_comm = ADS1115_COMM();

SPIClass spi {SPIClass()};
float dataTable[16];
int sizeOfDataTable {16};
float *dataPtr {dataTable};

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Program Begin, Uno SPI Slave, I2C AICard"); 
    Serial.println(sizeof(float));
    ads_comm.setup();
    spi.slaveInit();
    spi.attachInterrupt();
    
}


void loop() {
    Serial.println("Executing loop");
    Serial.println("Scanning I2C Channels");
    ads_comm.scanSingleEnded();
    // mapRawDataToTable();
    mapDataToTable();
    Serial.println("Sending Data Via SPI");
    spiTransmit(&spi, dataTable, sizeOfDataTable);
    printDataTable();
    // delay(3000);
}

void mapDataToTable(){
    resetPtr();
    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < 4; j++)
        {
            *dataPtr++ = ads_comm.readAnalogValueFrom(i,j);
        }        
    }
    resetPtr();
}

void mapRawDataToTable(){
    resetPtr();
    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < 4; j++)
        {
            *dataPtr++ = ads_comm.readRawValueFrom(i,j);
        }        
    }
    resetPtr();
}

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

ISR(SPI_STC_vect){
    Serial.println("Interrupt called");
}