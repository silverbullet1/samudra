#include "utils.h"

#include <stdint.h>


// TODO move this somewhere nice
uint16_t util::crc16(void *buffer, uint16_t len)
{
	// http://www.mycal.net/?cpath=/Archive/&id=567&action=9/
	uint8_t *buff = (uint8_t *)buffer;
	uint16_t crcvalue = 0xFFFF; // Initial crc
	uint16_t data = 0;
	int i;
	for (i=0; i<len; i++) {
		data = (crcvalue ^ buff[i]) & 0xFF;
		data = (data ^ (data << 4)) & 0xFF;
		data = (data << 8) ^ (data << 3) ^ (data >> 4);
		crcvalue=((crcvalue >> 8) ^ data);
	}
	return crcvalue;
}