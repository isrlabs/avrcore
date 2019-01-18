#include <avr/io.h>

#include <avrcore/serial.h>

void
serial_init(uint32_t baud, uint8_t ffmt)
{
	int	ubrr;

	ubrr = (uint8_t)SERIAL_SPEED(baud);
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	if (0 == ffmt)
		ffmt = SERIAL_8N1;
	UCSR0C = ffmt;
}


void
serial_block_transmit_byte(unsigned char b)
{
	while (!(UCSR0A & (1 << UDRE0))) ;
	UDR0 = b;
}


void
serial_transmit(uint8_t *data, uint8_t len)
{
	unsigned int	curbyte = 0;
	while (curbyte < len)
		serial_block_transmit_byte(data[curbyte++]);
}


unsigned char
serial_block_receive_byte()
{
	while (!(UCSR0A & (1 << RXC0))) ;
	return UDR0;
}


void
serial_print(char *data)
{
	while (*data != '\0') {
		serial_block_transmit_byte(*data);
		data++;
	}
}


void
serial_println(char *data)
{
	serial_print(data);
	serial_block_transmit_byte('\r');
	serial_block_transmit_byte('\n');
}
