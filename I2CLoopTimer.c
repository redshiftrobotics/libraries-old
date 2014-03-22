
#include "drivers/hitechnic-gyro.h"
#include "GyroLibrary.h"

void Gyro_Start()
{
	float rotSpeed = 0;
  float heading = 0;
  HTGYROstartCal(Gyro);
  time1[T1] = 0;
  StartTask(UpdateGyro);
}
