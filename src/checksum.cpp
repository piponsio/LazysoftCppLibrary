#include <lazysoft/checksum.hpp>

#define X25_INIT_CRC 0xffff
#define X25_VALIDATE_CRC 0xf0b8

/**
*Original Code:
*https://os.mbed.com/users/shimniok/code/AVC_2012/file/826c6171fc1b/MAVlink/include/checksum.h/
*Original Project:
*https://os.mbed.com/users/shimniok/code/AVC_2012/
**/

/**
 * @brief Accumulate the X.25 CRC by adding one char at a time.
 *
 * The checksum function adds the hash of one char at a time to the
 * 16 bit checksum (uint16_t).
 *
 * @param data new char to hash
 * @param crcAccum the already accumulated checksum
 **/
void Checksum::crc_accumulate(uint8_t data, uint16_t *crcAccum){
        /*Accumulate one byte of data into the CRC*/
        uint8_t tmp;

        tmp=data ^ (uint8_t)(*crcAccum &0xff);
        tmp^= (tmp<<4);
        *crcAccum = (*crcAccum>>8) ^ (tmp<<8) ^ (tmp <<3) ^ (tmp>>4);
}

/**
 * @brief Initiliaze the buffer for the X.25 CRC
 *
 * @param crcAccum the 16 bit X.25 CRC
 */
void Checksum::crc_init(uint16_t* crcAccum){
        *crcAccum = X25_INIT_CRC;
}

/**
 * @brief Calculates the X.25 checksum on a byte buffer
 *
 * @param  pBuffer buffer containing the byte array to hash
 * @param  length  length of the byte array
 * @return the checksum over the buffer bytes
 **/
uint16_t Checksum::crc_calculate(uint8_t* pBuffer, int length){

        // For a "message" of length bytes contained in the unsigned char array
        // pointed to by pBuffer, calculate the CRC
        // crcCalculate(unsigned char* pBuffer, int length, unsigned short* checkC$

        uint16_t crcTmp;
        //uint16_t tmp;
        uint8_t* pTmp;
        int i;

        pTmp=pBuffer;


        /* init crcTmp */
        crc_init(&crcTmp);

        for (i = 0; i < length; i++){
                crc_accumulate(*pTmp++, &crcTmp);
        }

        /* This is currently not needed, as only the checksum over payload should $
        tmp = crcTmp;
        crcAccumulate((unsigned char)(~crcTmp & 0xff),&tmp);
        crcAccumulate((unsigned char)((~crcTmp>>8)&0xff),&tmp);
        *checkConst = tmp;
        */
        return(crcTmp);
}
