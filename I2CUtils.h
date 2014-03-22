#include "drivers/common.h"

int I2CUtils_GetIntFromPort(tSensors port) {
	switch (port) {
		case S1:
			return 1;
		case S2:
			return 2;
		case S3:
			return 3;
		case S4:
			return 4;
		default:
			// TODO: throw a fatal error here
			return 0;
	}
}
