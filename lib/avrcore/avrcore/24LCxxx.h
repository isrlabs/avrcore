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


#define		EEPROM_BASE_ADDRESS	0x50
#define		EEPROM_ADDRESS_BITS(a0, a1, a2) ((a2 << 2) | (a1 << 1) | a2)


uint8_t		eeprom_write(uint8_t device, uint16_t address, uint8_t data);
uint8_t		eeprom_read(uint8_t device, uint16_t address);
uint8_t		eeprom_write_buffer(uint8_t device, uint16_t address,
				    uint8_t *data, uint8_t datalen);
uint8_t		eeprom_read_buffer(uint8_t device, uint16_t address,
				   uint8_t *data, uint8_t datalen);
uint8_t		eeprom_write_wait(uint8_t device);


#endif /* __AVRCORE_24LCXXX */
