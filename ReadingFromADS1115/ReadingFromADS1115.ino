#include <ADS1115_COMM.h>

ADS1115_COMM ads_comm = ADS1115_COMM();

void setup()
{
	Serial.begin(9600);
	Serial.println("Start Monitoring Analog Inputs");
}

void loop()
{
	ads_comm.scanSingleEnded();
	Serial.print("Ch 1 Raw input:");
	Serial.println(ads_comm.readRawValueFrom(0,0));

	Serial.print("Ch 1 Analog input:");
	Serial.println(ads_comm.readAnalogValueFrom(0,0));

	delay(2000);
}
