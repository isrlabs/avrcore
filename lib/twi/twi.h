/*
 * Copyright (c) 2019 Kyle Isom <kyle@imap.cc>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * lib/twi/twi.h
 * AVR two-wire (e.g. I2C) master
 *
 * This library implements basic TWI primitives that can be used as building
 * blocks for other peripheral libraries. It currently requires hardware
 * support for TWI; this precludes using this with the tiny84/85.
 *
 * Unless the board already supports it, 4.7K resistors should be used to
 * pull SDA and SCL up to the proper voltage.
 *
 * Note: On the Arduino Uno, SDA is pin A4 and SCL is pin A5.
 *
 */


#ifndef __AVRCORE_TWI_H
#define __AVRCORE_TWI_H


#include <avr/io.h>
#include <util/twi.h>


/*
 * The TWI_SCL definitions include the two common TWI bus speeds.
 */
#define		TWI_SCL_SLOW	100000UL
#define		TWI_SCL_FAST	400000UL

/*
 * TWI_STATUS indicates the result of an operation.
 */
#define		TWI_STATUS_ACK		0 /* Slave sent an ACK. */
#define		TWI_STATUS_NACK		1 /* Slave sent a NAK. */
#define		TWI_STATUS_PROTO	2 /* A TWI protocol error occurred. */


/*
 * twi_init initialises the device as a TWI master with a 100kHz bus.
 */
void		twi_init(void);

/*
 * twi_init_fast initialises the device as a TWI master with a 400kHz bus.
 */
void		twi_init_fast(void);

/*
 * twi_sendto sends a start condition and writes the device address to the
 * bus. The address should be unshifted. If the function fails, a stop
 * condition is sent.
 */
uint8_t		twi_sendto(uint8_t);

/*
 * twi_recvfrom sends a start condition and writes the device address to
 * the bus. The address should be unshifted. If the function fails, a stop
 * condition is sent.
 */
uint8_t		twi_recvfrom(uint8_t);

/*
 * twi_write writes a byte to the previously addressed device.
 */
uint8_t		twi_write(uint8_t);

/*
 * twi_read attempts to read a byte from the bus. It returns the device's
 * response.
 */
uint8_t		twi_read(uint8_t *);

/*
 * twi_read_multi attempts to read a byte from the bus, expecting more
 * data to be sent.
 */
uint8_t		twi_read_multi(uint8_t *);


/*
 * twi_stop sends a stop condition to the bus and waits for the bus to
 * be released.
 */
inline void
twi_stop(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	while (TWCR & _BV(TWSTO)) ; /* wait for bus release */
}


/*
 * twi_start sends a start condition to the bus.
 */
inline void
twi_start(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
}


/*
 * twi_clear readies the bus for transmission.
 */
inline void
twi_clear(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN);
}


/*
 * twi_wait waits for the bus to be ready.
 */
inline uint8_t
twi_wait(void)
{
	uint8_t	status;
	while ((TWCR & _BV(TWINT)) == 0) ;
	status = TW_STATUS & 0xF8; /* mask prescaler bits */
	return status;
}


#endif /* __AVRCORE_TWI_H */
