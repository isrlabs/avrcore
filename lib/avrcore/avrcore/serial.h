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
 * lib/avrcore/avrcore/serial.h
 * AVR UART library
 *
 * This library implements basic UART primitives for transmitting and
 * receiving data on the UART. It assumes hardware support for the UART.
 */


#ifndef __AVRCORE_SERIAL_H
#define __AVRCORE_SERIAL_H


#include <stdint.h>


/*
 * serial_transmit waits until the transmit buffer is ready, then sends
 * a buffer to the UART is complete.
 */
void		serial_transmit(uint8_t *, uint8_t);

/*
 * serial_print writes a string to the UART, stopping when it encounters
 * a NUL byte.
 */
void		serial_print(char *);

/*
 * serial_println writes a string to the UART, stopping when it encounters
 * a NUL byte. Then, it sends a carriage return and newline.
 */
void		serial_println(char *);

/*
 * serial_hexdump writes a hex dump to the UART.
 */
void		serial_hexdump(uint8_t *, uint8_t);

/*
 * serial_newline writes a newline to the UART.
 */
void		serial_newline(void);


#endif /* __AVRCORE_SERIAL_H */
