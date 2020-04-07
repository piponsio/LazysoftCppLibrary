#ifndef _STORM32_COMMAND_HPP_
#define _STORM32_COMMAND_HPP_

#include <string>
#include <chrono>
#include <fstream>

#include <lazysoft/crc.hpp>
#include <lazysoft/serial.hpp>

class Storm32_command{
	private:
		int size;
		int pre_size;
		int listen_size;
		bool log = 0;
		double angles[3];

		uint8_t* buffer;
		uint8_t* pre_buffer;
		uint8_t* listen_buffer;

		std::chrono::microseconds time_listen;

		std::ofstream* outfile_log = NULL;
		std::string path_log;

		Serial* com;

		uint8_t* listen(uint8_t byte2listen = 0, std::chrono::microseconds max_time = std::chrono::microseconds(10000));

	public:

		Storm32_command(const char* dev = "/dev/ttyACM0", speed_t baud = B9600);
		~Storm32_command();

		void startLog(std::string path);
		void closeLog();

		double* getAngles();
		double getAngle(int i = 0);

		uint8_t* setAngle(float pitch, float roll, float yaw);
		uint8_t* setAngle(double pitch, double roll, double yaw);

		uint8_t* getVersion();
		uint8_t* getDataFields(const char* live_data);


};
#endif
