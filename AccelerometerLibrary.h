#include "drivers/hitechnic-accelerometer.h"

int XRotation = 0;
int YRotation = 0;
int ZRotation = 0;

int AccelerometerX()
{
	HTACreadAllAxes(Accelerometer, XRotation, YRotation, ZRotation);
	return XRotation;
}
int AccelerometerY()
{
	HTACreadAllAxes(Accelerometer, XRotation, YRotation, ZRotation);
	return YRotation;
}
int AccelerometerZ()
{
	HTACreadAllAxes(Accelerometer, XRotation, YRotation, ZRotation);
	return ZRotation;
}
