#include "twi.h"

uint8_t
eeprom_write(uint8_t device, uint16_t address, uint8_t data)
{
	uint8_t	ret;

	ret = twi_sendto(device);
	if (ret) {
		return 1;
	}

	ret = twi_write((address & 0xFF00) >> 8);
	if (ret) {
		ret = 1;
		goto eeprom_write_stop;
	}

	ret = twi_write((address & 0xFF));
	if (ret) {
		ret = 1;
		goto eeprom_write_stop;
	}

	ret = twi_write(data);
	if (ret) {
		ret = 1;
		goto eeprom_write_stop;
		return 1;
	}

	ret = 0;

eeprom_write_stop:
	twi_stop();
	return ret;	
}


uint8_t
eeprom_read(uint8_t device, uint16_t address, uint8_t *data)
{
	uint8_t	ret;

	ret = twi_sendto(device);
	if (ret) {
		return 1;
	}

	ret = twi_write((address & 0xFF00) >> 8);
	if (ret) {
		ret = 1;
		goto eeprom_read_stop;
	}

	ret = twi_write((address & 0xFF));
	if (ret) {
		ret = 1;
		goto eeprom_read_stop;
	}

	twi_stop();
	ret = twi_recvfrom(device);
	if (ret) {
		ret = 1;
		goto eeprom_read_stop;
	}

	ret = twi_read(data);
	if (ret) {
		ret = 1;
		goto eeprom_read_stop;
	}

	ret = 0;

eeprom_read_stop:
	twi_stop();
	return ret;	
}


uint8_t
eeprom_write_buffer(uint8_t device, uint16_t address, uint8_t *data,
		    uint8_t datalen)
{
	uint8_t	i;
	uint8_t	ret;

	ret = twi_sendto(device);
	if (ret) {
		return 1;
	}

	ret = twi_write((address & 0xFF00) >> 8);
	if (ret) {
		ret = 1;
		goto eeprom_writebuf_stop;
	}

	ret = twi_write((address & 0xFF));
	if (ret) {
		ret = 1;
		goto eeprom_writebuf_stop;
	}

	for (i = 0; i < datalen; i++) {
		ret = twi_write(*(data++));
		if (ret) {
			ret = 1;
			goto eeprom_writebuf_stop;
			return 1;
		}
	}

	ret = 0;

eeprom_writebuf_stop:
	twi_stop();
	return ret;	
}


uint8_t
eeprom_read_buffer(uint8_t device, uint16_t address, uint8_t *data,
		   uint8_t datalen)
{
	uint8_t	i;
	uint8_t	ret;

	ret = twi_sendto(device);
	if (ret) {
		return 1;
	}

	ret = twi_write((address & 0xFF00) >> 8);
	if (ret) {
		ret = 1;
		goto eeprom_readbuf_stop;
	}

	ret = twi_write((address & 0xFF));
	if (ret) {
		ret = 1;
		goto eeprom_readbuf_stop;
	}

	twi_stop();
	ret = twi_recvfrom(device);
	if (ret) {
		ret = 1;
		goto eeprom_readbuf_stop;
	}

	for (i = 0; i < datalen-1; i++) {
		ret = twi_read_multi(data++);
		if (ret) {
			ret = 1;
			goto eeprom_readbuf_stop;
		}
	}

	ret = twi_read(data);
	if (ret != TWI_STATUS_NACK) {
		ret = 1;
		goto eeprom_readbuf_stop;
	}

	ret = 0;

eeprom_readbuf_stop:
	twi_stop();
	return ret;	
}


uint8_t
eeprom_write_wait(uint8_t device)
{
	uint8_t	i;
	uint8_t	ret;

	for (i = 0; i < 128; i++) {
		ret = twi_sendto(device);
		if (ret == TWI_STATUS_ACK) {
			break;
		}
	}

	if (ret == TWI_STATUS_ACK) {
		return 0;
	}

	return 1;
}

