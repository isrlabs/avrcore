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
 * lib/avrcore/avrcore/uart.h
 * AVR UART library
 *
 * This library implements basic UART primitives for transmitting and
 * receiving data on the UART. It assumes hardware support for the UART.
 */


#ifndef __AVRCORE_UART_H
#define __AVRCORE_UART_H


#include <avr/io.h>


#ifndef F_CPU
#error F_CPU is not defined.
#endif


/*
 * SERIAL_SPEED is a utility for calculating the correct register value
 * for a given baudrate.
 */
#define UART_SPEED(bps)	((F_CPU / (bps) / 16) - 1)

/*
 * FRAME_8N1 is the register value for the common 8N1 frame format.
 */
#define		FRAME_8N1	(3 << UCSZ00)


/*
 * uart_init sets up the UART, taking as arguments the baudrate and
 * frame format. If the frame format is 0, the standard 8N1 format is
 * used.
 */
void		uart_init(uint32_t, uint8_t);

/*
 * uart_block_transmit_byte waits until the transmit buffer is ready,
 * then puts the byte on the transmit buffer.
 */
void		uart_block_transmit_byte(uint8_t);


/*
 * uart_block_receive_byte reads a byte from the UART, blocking until a
 * byte is available.
 */
uint8_t		uart_block_receive_byte(void);


#endif /* __AVRCORE_UART_H */
