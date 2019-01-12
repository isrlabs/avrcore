/*
 * twi.h
 * I2C library for avrcore.
 */

#ifndef __AVRCORE_TWI_H
#define __AVRCORE_TWI_H

#define TWI_ATTEMPTS	128

class TWI {
public:
	TWI(bool fast);
	uint8_t	sendto(uint16_t);
private:
	uint8_t	status;
};


#endif
