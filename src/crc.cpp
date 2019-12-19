#include <lazysoft/crc.hpp>
#include <iostream>

uint16_t Crc::mcrf4xx(uint8_t *data, uint16_t len){
	return crc16(data, len, 0x1021, 0xFFFF, 0x0000);
}
uint16_t Crc::arc(uint8_t *data, uint16_t len){
	return crc16(data, len, 0x8005, 0x0000, 0x0000);
}
uint16_t Crc::crc16(uint8_t *data, uint16_t size, uint16_t poly, uint16_t init, uint16_t xorOut){

  	uint16_t crc = 0;

	uint8_t* temp_data = NULL;
	temp_data = static_cast<uint8_t *>(malloc(sizeof(uint8_t)*size));
	if(temp_data == NULL) std::cout << "MALLOC FULL\n\r";
	else{
		uint8_t* original_dir = temp_data;

		memcpy(temp_data, data, size);
		uint16_t out = 0;
    		int bits_read = 0, bit_flag;


		if(size > 1) *temp_data ^= init>>8;
		if(size > 0) *(temp_data+1) ^= init;

		if(temp_data == NULL) return 0;

		while(size > 0){
       		 	bit_flag = out >> 15;

	 	       	out <<= 1;
        		out |= (*temp_data >> bits_read) & 1;

	        	bits_read++;
        		if(bits_read > 7){
            			bits_read = 0;
            			temp_data++;
            			size--;
        		}

	        	if(bit_flag) out ^= poly;
		}
		free(original_dir);
		int i;
	    	for(i = 0; i < 16; ++i){
	        	bit_flag = out >> 15;
	        	out <<= 1;
	        	if(bit_flag) out ^= poly;
		}

	//  	uint16_t crc = 0;
	    	i = 0x8000;
	    	int j = 0x0001;
	    	for (; i != 0; i >>=1, j <<= 1) {
	    	    if (i & out) crc |= j;
	    	}
	//        std::cout << "\n\r---CRC---\n\r";
	//        std::cout << std::hex << +(crc^xorOut);
	//        std::cout << "\n\r---------\n\r";
	}
	    	return (crc ^ xorOut);
}


/*
uint16_t Checksum::crc16(uint8_t *temp_data, uint16_t size, uint16_t poly, uint16_t init, uint16_t xorOut){
	uint16_t crc = init;
	while (size--){
		crc ^= *temp_data++;
		for (unsigned k = 0; k < 8; k++) crc = crc & 1 ? (crc >> 1) ^ 0xa001 : crc >> 1;
	}
	std::cout << "\n\r";
	std::cout << (crc^xorOut);
	std::cout << "\n\r";
	return (crc^xorOut);
}
*/
