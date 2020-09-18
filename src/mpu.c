#include "i2ccom.h"
#include "mpu.h"


//******MPU Defintion******

//For storing settings of the MPU
struct MPU_s {
	int accelSensitivity;
	int gyroSensitivity;
};

struct MPU_s mpu = {
	.accelSensitivity = TWO_G_SENSITIVITY,
	.gyroSensitivity = ZERO_SENSITIVITY
};

//***************Initilization Functions*************************

/*
*	Wakes MPU up by setting sleep bit (6) in PWR_MGMT_1 (107) to 0.
*
*
*/
void wakeMPU() {
	//Reset entire register to 0. Kind of overboard, and has 
	//the poential to overwrite other settings, but this function
	//will most likely only be called when setting the MPU up. If not
	//modify this to only write 0 to bit 6.
	writeRegister(PWR_MGMT_1,0);
}

/*
* Resets entire MPU by setting reset bit (7) in PWR_MGMT_1 (107) to 1
*/

void resetMPU() {
	writeRegister(PWR_MGMT_1, DEVICE_RESET);
}


//*************Data Aquistion**********

double readTemp() {
	uint8_t rawTemp[2];
	//Read two consecutive registers from TEMP_OUT_H into the buffer rawTemp
	readRegister(TEMP_OUT_H, rawTemp, 2);
	//Need to negate becasue we read the 2's complement of the value
	//Debug print
	//printf("Raw reg values read: TEMP_H: %d, TEMP_L: %d\n", rawTemp[0], rawTemp[1]);
	int16_t combined =(uint16_t)((rawTemp[0] << 8) | rawTemp[1]);
	return (double) combined / 340 + 36.53;
}

double readAccel(Axis axis) {
	uint16_t accelRegs[] = {ACCEL_XOUT_H, ACCEL_YOUT_H, ACCEL_ZOUT_H};
	uint8_t rawAccel[2];
	//Read two consecutive registers from the specfied Accel High Register
	readRegister(accelRegs[axis], rawAccel, 2);
	int16_t raw16 = (rawAccel[0] << 8) | rawAccel[1];
	//Stored as 16-bit 2's complement value
	return ((double) -raw16) / mpu.accelSensitivity;	
}

double readGyro(Axis axis) {
	uint16_t gyroRegs[] = {GYRO_XOUT_H, GYRO_YOUT_H, GYRO_ZOUT_H};
	uint8_t rawGyro[2];
	//Read two consecutive registers from the specfied Gyro High Register
	readRegister(gyroRegs[axis], rawGyro, 2);
	int16_t raw16 = (rawGyro[0] << 8) | rawGyro[1];
	//Stored as 16-bit 2's complement value
	return ((double) -raw16) / mpu.gyroSensitivity;	
}

