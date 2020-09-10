#include "i2ccom.h"
#include "main.h"
#include "mpu.h"

#include <stdio.h>

int main() {
	initBus(MPU6050_ADDRESS);
	uint8_t addr = -1;
	readRegister(WHO_AM_I, &addr, 1);
	printf("%#02x\n", addr);
	printf("%d\n%d\n%d\n", accel[accelLabel.x], accel[accelLabel.y], accel[acelLabel.z]);

}
