#include <avrcore/uart.h>
#include <avrcore/serial.h>


void
serial_transmit(uint8_t *data, uint8_t len)
{
	unsigned int	curbyte = 0;
	while (curbyte < len)
		uart_block_transmit_byte(data[curbyte++]);
}


void
serial_print(char *data)
{
	while (*data != '\0') {
		uart_block_transmit_byte(*data);
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
		uart_block_transmit_byte(hv[0]);
		uart_block_transmit_byte(hv[1]);
		if (i < (buflen - 1)) uart_block_transmit_byte(0x20);
	}
}


void
serial_newline()
{
	uart_block_transmit_byte('\r');
	uart_block_transmit_byte('\n');
}
