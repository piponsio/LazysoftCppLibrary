#ifndef _CRC_HPP_
#define _CRC_HPP_

#include <cstring>
#include <cstdint>
#include <cstddef>

class Crc{
	public:
		static uint16_t crc16(uint8_t *data, uint16_t size, uint16_t poly, uint16_t init, uint16_t xorOut);
		static uint16_t mcrf4xx(uint8_t *data, uint16_t size);
		static uint16_t arc(uint8_t *data, uint16_t size);
};
#endif
