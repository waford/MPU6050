/*
 * mpu.h
 *
 *  Created on: Sep 11, 2020
 *      Author: waford
 */

#ifndef MPU_H
#define MPU_H

//Helpful: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

#define ACCEL_CONFIG 	(0x1C)
#define TWO_G 			(0 << 3)
#define FOUR_G 			(1 << 3)
#define EIGHT_G 		(2 << 3)
#define SIXTEEN_G		(3 << 3)


/*
 * This register specifies the divider from the gyroscope output
 * rate used to generate the Sample Rate for the MPU-60X0.
 * Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
 * where Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG= 0 or 7),
 * and 1kHz when the DLPF is enabled(see Register 26).
 */
#define SMPRT_DIV		(0x19)

//This  register  configures  the  external Frame  Synchronization  (FSYNC)pin  sampling  and  the Digital Low Pass Filter (DLPF)
//setting for both the gyroscopes and accelerometers. For info of config data, see pg13.
#define CONFIG			(0x1A)

//This register determines which sensor measurements are loaded into the FIFO buffer.
#define FIFO_EN			(0x23)
#define TEMP_FIFO_EN	(1<<7)
#define XG_FIFO_EN		(1<<6)
#define YG_FIFO_EN		(1<<5)
#define ZG_FIFO_EN		(1<<4)
#define ACCEL_FIFO_EN	(1<<3)
#define SLV2_FIFO_EN	(1<<2)
#define SLV1_FIFO_EN	(1<<1)
#define SLV0_FIFO_EN	(1<<0)

#define ACCEL_XOUT_H 	(0x3B)
#define ACCEL_XOUT_L 	(0x3C)
#define ACCEL_YOUT_H 	(0x3D)
#define ACCEL_YOUT_L 	(0x3E)
#define ACCEL_ZOUT_H 	(0x3F)
#define ACCEL_ZOUT_L 	(0x40)

//High and Low bit temperature registers
#define TEMP_OUT_H		(0x41)
#define TEMP_OUT_L		(0x42)

// User control register and associated bit values
#define USER_CTRL 		(0x6A)
#define FIFO_EN_BIT		(1<<6)
#define I2C_MST_EN		(1<<5)
#define I2C_IF_DIS		(0)
#define FIFO_RESET		(1<<2)
#define I2C_MST_RESET	(1<<1)
#define SIG_COND_RESET	(1<<0)

//Power Management 1 Register and associated bit values
#define PWR_MGMT_1		(0x6B)
#define DEVICE_RESET	(1<<7)
#define SLEEP			(1<<6)
#define CYCLE			(1<<5)
#define TEMP_DIS		(1<<3)
//NOTE: There are 8 possible clock sources. I will probably only be using 0, so not adding them

//Power Management 2 Register. If this becomes relevant, I will add flags
#define PWR_MGMT_2		(0x6C)

//High and Low Bit registers for number of samples currently in FIFO buffer. I might think of adding
//double register read functionality if relevant... maybe not.
#define FIFO_COUNT_H	(0x72)
#define FIFO_COUNT_L	(0x73)

//This register is used to read and write data from the FIFO buffer.
#define FIFO_R_W		(0x74)

#define WHO_AM_I		(0x75)

#define MPU6050_ADDRESS (0x68)


//LSB/G
#define Two_G_Sensitivity (16384)
#define Four_G_Sensitivity (8192)
#define Eight_G_Sensitivity (4096)
#define Sixteen_G_Sensitivity (2048)

#define G (9.81)

//Function Definitions

#endif

