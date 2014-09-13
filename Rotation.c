#include "drivers/hitechnic-protoboard.h"

int RawReadingToDegrees(int NineBitNumber)
{
	float Slope = 360.0 / 512.0;
	float Degrees = Slope * (float)NineBitNumber - 180.0;
	return (int)(Degrees);
}

//checks if the sensor is connected to the robot
bool Rotation_SensorConnected()
{
	if (!HTPBsetupIO(HTPB, 0x10))
  {
		return false;
  }
  return true;
}

float Rotation_Degrees()
{
  int AnalogPins = 0;
  byte DigitalPins = 0;
  int RawReading = 0;

	//reset the reading value
  RawReading = 0;

	//get the analog values
	for(int i = 0; i < 5; i++)
	{
		AnalogPins = HTPBreadADC(HTPB, i, 10);

		if (AnalogPins > 512)
		{
			RawReading += (1 << (4 + (4 - i));
		}
	}

	//get the digital values
  DigitalPins = HTPBreadIO(HTPB, 0x3F);
  RawReading += (DigitalPins&0x01) << 3;
  RawReading += (DigitalPins&0x02) << 1;
  RawReading += (DigitalPins&0x04) >> 1;
  RawReading += (DigitalPins&0x08) >> 3;

  //convert the reading to 360 degrees
  return RawReadingToDegrees(RawReading);
}
