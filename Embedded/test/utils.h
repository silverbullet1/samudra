#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>

namespace util {
	
	uint16_t crc16(void *buffer, uint16_t len);
}

#endif