#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include "main.h"

int file_i2c;

int readRegister(uint8_t regAddress, uint8_t buffer[], int length) {
	if (write(file_i2c, &regAddress, 1) != 1) {
		printf("Something terrible has gone wrong!\n");
		return -1;
	} else {
		if(read(file_i2c, buffer, length) != length) {
			printf("Something terrible has gone wrong!\n");
			return -1;
		} else {
			return length;
		}
	}
}

void initMPU() {
	//First reset de
	uint8_t initBuff[2];
	initBuff[0] = PWR_MGMT_1;
	initBuff[1] = DEVICE_RESET;
	if((write(file_i2c, initBuff, 2) != 2)) {
		printf("Failed to init mpu\n");
		return;
	}
	//Turn of sleep
	initBuff[1] = 0;
	if((write(file_i2c, initBuff, 2) != 2)) {
		printf("Failed to init mpu\n");
		return;
	}
}

void configureAccelerometer(uint8_t flags) {
	uint8_t buff[2];
	buff[0] = ACCEL_CONFIG;
	buff[1] = flags;
	if((write(file_i2c, buff, 2) != 2)) {
		printf("Failed to init mpu\n");
		return;
	}
}

double readTemp() {
	uint8_t buff[2];
	readRegister(TEMP_OUT_H, buff, 2);
	int16_t rawTemp = (buff[0] << 8) | buff[1];
	return ((double) rawTemp / 340) + 36.53;
}

double readXAccel() {
	uint8_t raw[2];
	readRegister(ACCEL_XOUT_H, raw, 2);
	int16_t raw16 = (raw[0] << 8) + raw[1];
	//Stored as 16-bit 2's complemnt value
	return ((double) -raw16) / Two_G_Sensitivity;
}

double readYAccel() {
	uint8_t raw[2];
	readRegister(ACCEL_YOUT_H, raw, 2);
	int16_t raw16 = (raw[0] << 8) + raw[1];
	//Stored as 16-bit 2's complemnt value
	return ((double) -raw16) / Two_G_Sensitivity;
}

double readZAccel() {
	uint8_t raw[2];
	readRegister(ACCEL_ZOUT_H, raw, 2);
	int16_t raw16 = (raw[0] << 8) | raw[1];
	//Stored as 16-bit 2's complemnt value
	return ((double) -raw16) / Two_G_Sensitivity;
}

int main() {
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0) {
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return 1;
	}
	if (ioctl(file_i2c, I2C_SLAVE, MPU6050_ADDRESS) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return 1;
	}
	initMPU();
	configureAccelerometer(TWO_G);
	while(1) {
		double xAccel = readXAccel();
		double yAccel = readYAccel();
		double zAccel = readZAccel();
		//double netAccel = sqrt(pow(xAccel,2) + pow(yAccel,2) + pow(zAccel,2));
		printf("X:%f, Y:%f, Z:%f\n", xAccel, yAccel, zAccel);
		sleep(0.5);
	}
	return 0;
}
