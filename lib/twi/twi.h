/*
 * twi.h
 * I2C library for avrcore.
 */


/**
 @file
 @defgroup isr_avrcore
 @code #include "twi.h" @endcode

 @brief AVR two-wire (e.g. I2C) master 
 
 This library implements basic TWI primitives that can be used as building
 blocks for other peripheral libraries. It currently requires hardware
 support for TWI; this precludes using this with the tiny84/85.

 Unless the board already supports it, 4.7K resistors should be used to pull
 SDA and SCL up to the proper voltage.

 @note
     On the Arduino Uno, SDA is pin and SCL is pin .

 */


#ifndef __AVRCORE_TWI_H
#define __AVRCORE_TWI_H


#include <avr/io.h>
#include <util/twi.h>


#define		TWI_SCL_SLOW	100000UL
#define		TWI_SCL_FAST	400000UL

#define		TWI_STATUS_ACK		0
#define		TWI_STATUS_NACK		1
#define		TWI_STATUS_PROTO	2


void		twi_init(void);
void		twi_init_fast(void);
uint8_t		twi_sendto(uint8_t);
uint8_t		twi_recvfrom(uint8_t);
uint8_t		twi_write(uint8_t);
uint8_t		twi_read(uint8_t *);


inline void
twi_stop(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	while (TWCR & _BV(TWSTO)) ; /* wait for bus release */
}


inline void
twi_start(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
}


inline void
twi_clear(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN);
}


inline uint8_t
twi_wait(void)
{
	uint8_t	status;
	while ((TWCR & _BV(TWINT)) == 0) ;
	status = TW_STATUS & 0xF8; /* mask prescaler bits */
	return status;
}


#endif /* __AVRCORE_TWI_H */
