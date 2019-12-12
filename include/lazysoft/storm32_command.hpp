#ifndef _STORM32_COMMAND_HPP_
#define _STORM32_COMMAND_HPP_

#include <iostream>
#include <bitset>

#include <cstring>
#include <chrono>
#include <lazysoft/checksum.hpp>
#include <lazysoft/serial.hpp>

class Storm32_command{
	public:
		int size;
		uint8_t* buffer;
		std::chrono::microseconds time_listen;

		double angles[3];

		Serial com;
		Storm32_command(const char* dev, speed_t baud);

		uint8_t* listen(uint8_t byte2listen, std::chrono::microseconds max_time);
		double* getAngles();

		uint8_t* getVersion();
		//uint8_t* getDataFields();
		uint8_t* getDataFields(const char* live_data);
		uint8_t* setAngle(float pitch, float roll, float yaw);

};
#endif
