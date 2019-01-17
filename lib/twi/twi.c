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

#define TWI_MAX_RESTARTS	128

uint8_t
twi_sendto(uint8_t device)
{
	/* question: is 255 bytes the max length for transmission? */
	uint8_t	status;
	uint8_t	restarts = 0;

begin_restart:
	if (restarts++ == TWI_MAX_RESTARTS) {
		goto begin_error;
	}
begin_begin:
	/* master start condition */
	twi_start();
	status = twi_wait();
	switch (status) {
	case TW_REP_START: /* fall through */
	case TW_START:
		break; /* OK */
	case TW_MT_ARB_LOST:
		/* master transmitter has lost arbitration */
		goto begin_begin;
	default:
		/* unknown error */
		goto begin_error;
	}

	/* write device address */
	TWDR = (device << 1) | TW_WRITE;
	twi_clear();
	status = twi_wait();
	switch (status) {
	case TW_MT_SLA_ACK:
		/* slave has acknowledged write */
		break;
	case TW_MT_SLA_NACK:
		/* slave has not acknowledge write */
		goto begin_restart;
	case TW_MT_ARB_LOST:
		/* master transmitter has lost arbitration */
		goto begin_begin;
	default:
		/* unknown error */
		goto begin_error;
	}

	if (status == TW_MT_SLA_ACK) {
		return 0;
	}

begin_error:
	twi_stop();
	return status;
}


uint8_t
twi_recvfrom(uint8_t device)
{
	/* question: is 255 bytes the max length for transmission? */
	uint8_t	status;
	uint8_t	restarts = 0;

recv_restart:
	if (restarts++ == TWI_MAX_RESTARTS) {
		goto recv_error;
	}
recv_begin:
	/* master start condition */
	twi_start();
	status = twi_wait();
	switch (status) {
	case TW_REP_START: /* fall through */
	case TW_START:
		break; /* OK */
	case TW_MT_ARB_LOST:
		/* master transmitter has lost arbitration */
		goto recv_begin;
	default:
		/* unknown error */
		goto recv_error;
	}

	/* write device address */
	TWDR = ((device << 1) | TW_READ);
	twi_clear();
	status = twi_wait();
	switch (status) {
	case TW_MT_SLA_ACK:
		/* slave has acknowledged write */
		break;
	case TW_MT_SLA_NACK:
		/* slave has not acknowledge write */
		goto recv_restart;
	case TW_MT_ARB_LOST:
		/* master transmitter has lost arbitration */
		goto recv_begin;
	default:
		/* unknown error */
		goto recv_error;
	}

	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	status = twi_wait();
	if (status == TW_MT_SLA_ACK) {
		return 0;
	}

recv_error:
	twi_stop();
	return status;

}


uint8_t
twi_write(uint8_t data)
{
	uint8_t	status;

	TWDR = data;
	twi_clear();
	status = twi_wait();
	return status;
}

uint8_t
twi_read(uint8_t *byte)
{
	uint8_t	status;

	TWCR = _BV(TWINT) | _BV(TWEN);
	twi_clear();
	status = twi_wait();	
	if (status == TW_MR_DATA_ACK) {
		*byte = TWDR;
		return 0;
	}

	return 1;
}
