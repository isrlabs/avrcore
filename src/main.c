#include <avr/io.h>
#include <avrcore/serial.h>
#include <avrcore/twi.h>
#include <avrcore/24LCxxx.h>


#define EEPROM		0x50


int
main(void)
{
	uint8_t	data[] = "avrcore";
	uint8_t	buf[13];
	uint8_t	i, ret;

	for (i = 0; i < 13; i++)
		buf[i] = 0; /* set up buf as a string */

	serial_init(9600, 0);
	serial_block_transmit_byte('>');

	twi_init();
	ret = eeprom_write_buffer(EEPROM, 0, data, 7);
	if (ret) {
		serial_block_transmit_byte('!');
		serial_block_transmit_byte(ret + 0x30);
		serial_block_transmit_byte('\r');
		serial_block_transmit_byte('\n');
		goto loop;
	}

	ret = eeprom_write_wait(EEPROM);
	if (ret) {
		serial_block_transmit_byte('!');
		serial_block_transmit_byte(ret + 0x30);
		serial_block_transmit_byte('\r');
		serial_block_transmit_byte('\n');
		goto loop;
	}
	
	ret = eeprom_read_buffer(EEPROM, 0, buf, 7);
	if (ret) {
		serial_block_transmit_byte('!');
		serial_block_transmit_byte(ret + 0x30);
		serial_block_transmit_byte('\r');
		serial_block_transmit_byte('\n');
		goto loop;
	} 

	serial_println((char *)buf);

loop:
	while (1) ;
}
