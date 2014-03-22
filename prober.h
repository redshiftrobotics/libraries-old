#include "saas_common.h"

int getSensorType(tSensors port)
{
		int sensorId;

		//initializes the arrays
		tByteArray I2Crequest;
		tByteArray I2Cresponse;

		//sets the number of bytes to send:
		I2Crequest[0] = 2;

		//sends the address as the first byte
		//no daisychain logic because that's only for multiplexors and servo/motor controllers
	  I2Crequest[1] = 0x02;

	  //sets the starting position to start sending data at
	  I2Crequest[2] = 0x10;

	  //writes the data, and gets the response
	  writeI2C(port, I2Crequest, I2Cresponse, 4);

	  return sensorId;
}
