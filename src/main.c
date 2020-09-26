#include "i2ccom.h"
#include "mpu.h"
#include "main.h"

#include <math.h>
#include <stdio.h>
#include <time.h>

#define MOVING_AVG_SIZE (100)

struct data {
	double accel[3];
	double gyro[3];
	double temp;
} data;

typedef struct movingAvg {
	double data[MOVING_AVG_SIZE];
	double mean;
	int index;
} movingAvg;


double updateMovingAvg(double value, movingAvg * mvAvg) {
	//Grab index value so we don't have to keep accesing mean for it
	int ind = mvAvg->index % MOVING_AVG_SIZE;
	//printf("Ind: %d\n", ind);
	(mvAvg->data)[ind] = value;
	ind++;
	double old = mvAvg->data[ind % MOVING_AVG_SIZE];
//	printf("Old: %.03f\r", old);
	 
	mvAvg->mean += (value - old) / MOVING_AVG_SIZE;
//	printf("Mean: %0.4f\n", mvAvg->mean);
	mvAvg->index = ind;
	return mvAvg->mean;
}

//Getting a bit dirty here
void initMovingAvg(movingAvg * mvAvg) {
	mvAvg->mean = 0;
	mvAvg->index = 0;
	for(int i = 0; i < MOVING_AVG_SIZE; i++) {
		(mvAvg->data)[i] = 0;
	}
}

int main() {
	initBus(MPU6050_ADDRESS);
	uint8_t addr = -1;
	readRegister(WHO_AM_I, &addr, 1);
	printf("%#02x\n", addr);
	wakeMPU();
//	calibrateGyroscope();
	movingAvg xAccel;
	movingAvg yAccel;
	movingAvg zAccel;
	initMovingAvg(&xAccel);
	initMovingAvg(&yAccel);
	initMovingAvg(&zAccel);
	
	movingAvg xGyro;
	initMovingAvg(&xGyro);

	while(1) {
		updateMovingAvg(readAccel(X), &xAccel);
	updateMovingAvg(readAccel(Y), &yAccel);
	updateMovingAvg(readAccel(Z), &zAccel);
	double mag = sqrt(pow(xAccel.mean,2) + pow(yAccel.mean,2) + pow(zAccel.mean,2));
	printf("XAccel %0.3f, YAccel %0.3f, ZAccel %0.3f, Magnitude: %0.3f  \r", xAccel.mean, yAccel.mean, zAccel.mean, mag);


	
}   
}
