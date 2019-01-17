/*
 * i2c.c
 * I2C library for avrcore.
 */


#include <avr/io.h>
#include <util/twi.h>
#include "twi.h"


/*
 * twi_init starts an I2C master with a 100kHz bus.
 */
void
twi_init()
{
	TWSR = 0;
	TWBR = ((F_CPU / 100000UL) - 16) / 2;
}


/*
 * twi_init starts an I2C master with a 400kHz bus.
 */
void
twi_init_fast()
{
	TWSR = 0;
	TWBR = ((F_CPU / 400000UL) - 16) / 2;
}


/*
 * twi_sendto starts a transmission to a device.
 */
uint8_t
twi_sendto(uint8_t address)
{
	uint8_t	twst;

	/* send start condition */
	twi_start();
	twst = twi_wait();
	if ((TW_START != twst) && (TW_REP_START != twst)) {
		return TWI_STATUS_PROTO;
	}

	/* send address | TW_WRITE */
	address = (address << 1) | TW_WRITE;
	TWDR = address;
	twi_clear();
	twst = twi_wait();
	switch (twst) {
	case TW_MT_SLA_ACK:
		return TWI_STATUS_ACK;
	case TW_MT_SLA_NACK:
		return TWI_STATUS_NACK;
	default:
		return TWI_STATUS_PROTO;
	}
}


/*
 * twi_write writes a byte to a previously-addressed device.
 */
uint8_t
twi_write(uint8_t data)
{
	uint8_t	twst;

	TWDR = data;
	twi_clear();
	twst = twi_wait();
	switch (twst) {
	case TW_MT_DATA_ACK:
		return TWI_STATUS_ACK;
	case TW_MT_DATA_NACK:
		return TWI_STATUS_NACK;
	default:
		return TWI_STATUS_PROTO;
	}
}


/*
 * recvfrom begins a request for data from a device.
 */
uint8_t
twi_recvfrom(uint8_t address)
{
	uint8_t	twst;

	/* send start condition */
	twi_start();
	twst = twi_wait();
	if ((TW_START != twst) && (TW_REP_START != twst)) {
		return TWI_STATUS_PROTO;
	}

	/* send address | TW_WRITE */
	address = (address << 1) + TW_READ;
	TWDR = address;
	twi_clear();
	twst = twi_wait();
	switch (twst) {
	case TW_MR_SLA_ACK:
		return TWI_STATUS_ACK;
	case TW_MR_SLA_NACK:
		return TWI_STATUS_NACK;
	default:
		return TWI_STATUS_PROTO;
	}
}


/*
 * twi_read attempts to read a byte with a NAK from a slave device.
 */
uint8_t
twi_read(uint8_t *data)
{
	uint8_t	twst;

	twi_clear();
	twst = twi_wait();

	switch (twst) {
	case TW_MR_DATA_ACK:
		*data = TWDR;
		return TWI_STATUS_ACK;
	case TW_MR_DATA_NACK:
		return TWI_STATUS_NACK;
	default:
		return TWI_STATUS_PROTO;
	}
}
