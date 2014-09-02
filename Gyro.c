#include "drivers/hitechnic-gyro.h"

float rotSpeed;
float heading;


task UpdateGyro;

task UpdateGyro()
{
	while(true)
	{
		//wait about 1 miliseconds
	  while (time1[T1] < 5)
	  {
	    wait1Msec(.01);
	  }

	  //find exact time waited and store in i
	  float i = time1[T1];

	  //reset timer
	  time1[T1]=0;

	  //get speed of rotation per second
	  rotSpeed = HTGYROreadRot(Gyro);

	  //multiply by seconds taken, and add to heading
	  heading += rotSpeed * (i / 1000);
	}
}

void Gyro_Start()
{
	float rotSpeed = 0;
  float heading = 0;
  HTGYROstartCal(Gyro);
  time1[T1] = 0;
  StartTask(UpdateGyro);
}

float Gyro_Heading()
{
		hogCPU();
		float i = heading;
		releaseCPU();
		return i;
}

void Gyro_Reset()
{
	heading = 0;
}
