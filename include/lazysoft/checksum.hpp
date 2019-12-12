#ifndef _CHECKSUM_HPP_
#define _CHECKSUM_HPP_

#include "cinttypes"

/**
 *
 *  CALCULATE THE CHECKSUM
 *
 */

class Checksum{
	public:
		//static inline void crc_accumulate(uint8_t data, uint16_t *crcAccum);
		static void crc_accumulate(uint8_t data, uint16_t *crcAccum);
		static void crc_init(uint16_t* crcAccum);
		static uint16_t crc_calculate(uint8_t* pBuffer, int length);

};
#endif
