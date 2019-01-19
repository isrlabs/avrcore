#include <avr/io.h>
#include <avrcore/uart.h>
#include <avrcore/serial.h>
#include <avrcore/twi.h>
#include <avrcore/24LCxxx.h>


#define EEPROM		0x50
#define WRSZ		7

int
main(void)
{
	/* uint8_t	data[] = "avrcore"; */
	uint8_t	buf[16];
	uint8_t	i, ret;

	for (i = 0; i < 16; i++)
		buf[i] = 0; /* set up buf as a string */

	uart_init(9600, 0);
	uart_block_transmit_byte('>');

	twi_init();
	/*
	 * ret = eeprom_write_buffer(EEPROM, 0, data, WRSZ);
	 * if (ret) {
	 * 	serial_block_transmit_byte('!');
	 * 	serial_block_transmit_byte(ret + 0x30);
	 * 	serial_block_transmit_byte('\r');
	 * 	serial_block_transmit_byte('\n');
	 * 	goto loop;
	 * }

	 * ret = eeprom_write_wait(EEPROM);
	 * if (ret) {
	 * 	serial_block_transmit_byte('!');
	 * 	serial_block_transmit_byte(ret + 0x30);
	 * 	serial_block_transmit_byte('\r');
	 * 	serial_block_transmit_byte('\n');
	 * 	goto loop;
	 * }
	 */
	
	ret = eeprom_read_buffer(EEPROM, 0, buf, WRSZ);
	if (ret) {
		uart_block_transmit_byte('!');
		uart_block_transmit_byte(ret + 0x30);
		uart_block_transmit_byte('\r');
		uart_block_transmit_byte('\n');
		goto loop;
	} 

	serial_hexdump(buf, 7);
	serial_newline();

loop:
	while (1) ;
}
