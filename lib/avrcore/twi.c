#include <avr/io.h>
#include <util/twi.h>

#include <avrcore/twi.h>


void
twi_init()
{
	TWSR = 0;
	TWBR = ((F_CPU / 100000UL) - 16) / 2;
}


void
twi_init_fast()
{
	TWSR = 0;
	TWBR = ((F_CPU / 400000UL) - 16) / 2;
}


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


uint8_t
twi_read(uint8_t *data)
{
	uint8_t	twst;

	twi_clear();
	twst = twi_wait();

	switch (twst) {
	case TW_MR_DATA_ACK:
		/*
		 * A NAK is expected, but if the device ends transmission,
		 * this byte may be useful.
		 */
		*data = TWDR;
		return TWI_STATUS_ACK;
	case TW_MR_DATA_NACK:
		*data = TWDR;
		return TWI_STATUS_NACK;
	default:
		return TWI_STATUS_PROTO;
	}
}


uint8_t
twi_read_multi(uint8_t *data)
{
	uint8_t	twst;

	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	twst = twi_wait();

	switch (twst) {
	case TW_MR_DATA_ACK:
		*data = TWDR;
		return TWI_STATUS_ACK;
	case TW_MR_DATA_NACK:
		/*
		 * An ACK is expected, but if the device ends transmission,
		 * this byte may be useful.
		 */
		*data = TWDR;
		return TWI_STATUS_NACK;
	default:
		return TWI_STATUS_PROTO;
	}

}
