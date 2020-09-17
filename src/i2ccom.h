#ifndef _i2ccom_h_
#define _i2ccom_h_
#include <stdint.h>


//Function Prototypes
int readRegister(uint8_t regAddress, uint8_t buffer[], int length);
int writeRegister(uint8_t regAddress, uint8_t value);
int initBus(uint8_t slaveAddress);

#endif
