#include <lazysoft/crc.hpp>

uint16_t Crc::crc16(uint8_t *temp_data, uint16_t size, uint16_t reversed_poly, uint16_t init, uint16_t xorOut){
	uint16_t crc = init;
	while (size--){
		crc ^= *temp_data++;
		for (unsigned k = 0; k < 8; k++) crc = crc & 1 ? (crc >> 1) ^ reversed_poly : crc >> 1;
	}
	return (crc^xorOut);
}

uint16_t Crc::mcrf4xx(uint8_t *data, uint16_t len){
// 0x8408 is a bit-revered of -> 0x1021 poly of mcrf4xx
	return crc16(data, len, 0x8408, 0xFFFF, 0x0000);
}
uint16_t Crc::arc(uint8_t *data, uint16_t len){
	return crc16(data, len, 0xA001, 0x0000, 0x0000);
}

