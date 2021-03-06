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
 * lib/avrcore/avrcore/24LCxxx.h
 * AVR two-wire (e.g. I2C) EEPROM peripheral library
 *
 * This library implements support for the 24LCXXX series of TWI EEPROMs.
 */


#ifndef __AVRCORE_24LCXXX
#define __AVRCORE_24LCXXX


#include "twi.h"


/*
 * EEPROM_BASE_ADDRESS is the base address for the 24LCxxx EEPROMs.
 * EEPROM_ADDRESS_BITS calculates the address given the address bits.
 * EEPROM_PAGE_SIZE calculates the max page size for an EEPROM.
 */
#define		EEPROM_BASE_ADDRESS	0x50
#define		EEPROM_ADDRESS(a0, a1, a2) \
		(EEPROM_BASE_ADDRESS | (a2 << 2) | (a1 << 1) | a2)
#define		EEPROM_PAGE_SIZE(bits)	(bits >> 2)


/*
 * eeprom_write writes a byte to the EEPROM.
 */
uint8_t		eeprom_write(uint8_t device, uint16_t address, uint8_t data);

/*
 * eeprom_read reads a byte from the EEPROM.
 */
uint8_t		eeprom_read(uint8_t device, uint16_t address);

/*
 * eeprom_write_buffer writes up to a page's worth of data from the EEPROM.
 */
uint8_t		eeprom_write_buffer(uint8_t device, uint16_t address,
				    uint8_t *data, uint8_t datalen);

/*
 * eeprom_read_buffer reads up to a page's worth of data from the EEPROM.
 */
uint8_t		eeprom_read_buffer(uint8_t device, uint16_t address,
				   uint8_t *data, uint8_t datalen);

/*
 * eeprom_write_wait performs ACK polling on the device.
 */
uint8_t		eeprom_write_wait(uint8_t device);


#endif /* __AVRCORE_24LCXXX */
