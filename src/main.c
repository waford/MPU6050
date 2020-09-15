#include "i2ccom.h"
#include "main.h"
#include "mpu.h"

#include <stdio.h>

struct data {
	double accel[3];
	double gyro[3];
}

int main() {
	initBus(MPU6050_ADDRESS);
	uint8_t addr = -1;
	readRegister(WHO_AM_I, &addr, 1);
	printf("%#02x\n", addr);
	printf("%f\n%f\n%f\n", accel[0], accel[1], accel[2]);

}
