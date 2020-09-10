#include "i2ccom.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

// Create file handle for device file
int file_i2c;

int readRegister(uint8_t regAddress, uint8_t buffer[], int length) {
	//Write address to i2c bus, along with the number of bytes (1) being sent.
	if (write(file_i2c, &regAddress, 1) != 1) {
		printf("Something terrible has gone wrong!\n");
		return -1;
	} else {
		//Read from the i2c bus into buffer a certian number of bytes
		if(read(file_i2c, buffer, length) != length) {
			printf("Something terrible has gone wrong!\n");
			return -1;
		} else {
			//If everything goes right, the number of bytes read should be returned. 
			return length;
		}
	}
}

//Initilizes the i2c bus for communicataion with the provided slave address
int initBus(uint8_t slaveAddress) {
	char *filename = (char*)"/dev/i2c-1";
	//Checks to make sure the i2c file is a legitament file handel
	if ((file_i2c = open(filename, O_RDWR)) < 0) {
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return 1;
	}
	if (ioctl(file_i2c, I2C_SLAVE, slaveAddress) != 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return 1;
	}
}
