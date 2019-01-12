#include <avr/io.h>
#include "serial.h"


int
main(void)
{
	unsigned char	ok[] = "ok\r\n";
	unsigned char	in;
	
	serial_init(9600, 0);
	serial_transmit(ok, 4);
	while (1) {
		in = serial_block_receive_byte();
		serial_block_transmit_byte(in);
	}
}
