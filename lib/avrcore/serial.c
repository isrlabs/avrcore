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
	serial_newline();
}


static inline void
hexify(uint8_t *byte)
{
	if (*byte < 0xA) {
		*byte += 0x30;
	} else {
		*byte = (*byte - 0xA) + 0x41;
	}
}

void
serial_hexdump(uint8_t *buf, uint8_t buflen)
{
	uint8_t	hv[2];
	uint8_t	 i;

	for (i = 0; i < buflen; i++) {
		hv[0] = ((buf[i] & 0xF0) >> 4);
		hv[1] = buf[i] & 0x0F;
		hexify(&hv[0]);
		hexify(&hv[1]);
		serial_block_transmit_byte(hv[0]);
		serial_block_transmit_byte(hv[1]);
		if (i < (buflen - 1)) serial_block_transmit_byte(0x20);
	}
}


void
serial_newline()
{
	serial_block_transmit_byte('\r');
	serial_block_transmit_byte('\n');
}
