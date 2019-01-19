#include <avr/io.h>
#include <avrcore/uart.h>


void
uart_init(uint32_t baud, uint8_t ffmt)
{
	int	ubrr;

	ubrr = (uint8_t)UART_SPEED(baud);
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	if (0 == ffmt)
		ffmt = FRAME_8N1;
	UCSR0C = ffmt;
}


void
uart_block_transmit_byte(unsigned char b)
{
	while (!(UCSR0A & (1 << UDRE0))) ;
	UDR0 = b;
}


uint8_t
uart_block_receive_byte()
{
	while (!(UCSR0A & (1 << RXC0))) ;
	return UDR0;
}
