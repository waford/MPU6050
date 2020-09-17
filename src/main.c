#include "i2ccom.h"
#include "mpu.h"
#include "main.h"

#include <stdio.h>

struct data {
	double accel[3];
	double gyro[3];
} data;

int main() {
	initBus(MPU6050_ADDRESS);
	uint8_t addr = -1;
	readRegister(WHO_AM_I, &addr, 1);
	printf("%#02x\n", addr);
	wakeMPU();
	resetMPU();
	double temp = -1;
	temp = readTemp();
	printf("Temp is %.02f Celcius\n", temp);

}
