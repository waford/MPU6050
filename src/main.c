#include "i2ccom.h"
#include "mpu.h"
#include "main.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

struct data {
	double accel[3];
	double gyro[3];
	double temp;
} data;

int main() {
	initBus(MPU6050_ADDRESS);
	uint8_t addr = -1;
	readRegister(WHO_AM_I, &addr, 1);
	printf("%#02x\n", addr);
	wakeMPU();
	double tempAvg = 0;
	int size = 300;
	double temps[size];
	for(int i = 0; i < size; i++) {
		temps[i] = 25;
	}
	int i = 0;
	while(1) {
		if(i >= size) {i=0;}
		double instTemp = readTemp();
		//printf("INSTTEMP: %0.2f, oldTEMP:%.2f, i:%d\n", instTemp, temps[(i-1) % size], i);
		temps[i] = instTemp;
		//Easy way first:
		tempAvg = 0;
		for(int j = 0; j < size; j++){
			tempAvg += (temps[j] / size);
		}
		i++;
		double xAccel = readAccel(X);
		double yAccel = readAccel(Y);
		double zAccel = readAccel(Z);
		double mag = sqrt(pow(xAccel,2) + pow(yAccel,2) + pow(zAccel,2));
		printf("Temp is %0.3f C, X-Accel: %0.3f, Y-Accel: %0.3f, Z-Accel: %0.3f, Mag: %0.3f\r", tempAvg, xAccel, yAccel, zAccel, mag);
	}
}
