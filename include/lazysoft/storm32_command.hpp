#ifndef _STORM32_COMMAND_HPP_
#define _STORM32_COMMAND_HPP_

#include <string>
#include <iostream>
#include <chrono>

#include <lazysoft/crc.hpp>
#include <lazysoft/serial.hpp>

class Storm32_command{
	public:
		int size;
		int pre_size;
		uint8_t* buffer;
		uint8_t* pre_buffer;
		std::chrono::microseconds time_listen;

		double angles[3];

		Serial com;
		Storm32_command(const char* dev, speed_t baud);

		uint8_t* listen(uint8_t byte2listen, std::chrono::microseconds max_time);
		double* getAngles();

		uint8_t* getVersion();
		uint8_t* getDataFields(const char* live_data);
		uint8_t* setAngle(float pitch, float roll, float yaw);
		uint8_t* setAngle(double pitch, double roll, double yaw);

};
#endif
