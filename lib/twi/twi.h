/*
 * twi.h
 * I2C library for avrcore.
 */

#ifndef __AVRCORE_TWI_H
#define __AVRCORE_TWI_H

#include <avr/io.h>
#include <util/twi.h>

#define TWI_ATTEMPTS	128

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


#endif
