#ifndef _STORM32_COMMAND_HPP_
#define _STORM32_COMMAND_HPP_

#include <string>
#include <iostream>
#include <chrono>
#include <fstream>

#include <lazysoft/crc.hpp>
#include <lazysoft/serial.hpp>

class Storm32_command{
	public:
		int size;
		int pre_size;
		int listen_size;

		uint8_t* buffer;
		uint8_t* pre_buffer;
		uint8_t* listen_buffer;

		std::ofstream* data_logger;
//		const char* data_logger_path;
		std::chrono::microseconds time_listen;

		double angles[3];

		Serial* com;
//		Storm32_command(const char* dev = NULL, speed_t baud = B0, std::fstream* data_logger = NULL);
		Storm32_command(Serial* com = NULL, std::fstream* data_logger = NULL);
		~Storm32_command();
		void setDataLogger(std::ofstream* data_logger);
	//	uint8_t* listen(uint8_t byte2listen, std::chrono::microseconds max_time);
		uint8_t* listen(uint8_t byte2listen = 0, std::chrono::microseconds max_time = std::chrono::microseconds(10000));
		double* getAngles();

		uint8_t* getVersion();
		uint8_t* getDataFields(const char* live_data);
		uint8_t* setAngle(float pitch, float roll, float yaw);
		uint8_t* setAngle(double pitch, double roll, double yaw);

};
#endif
