#ifndef _SERIAL_HPP_
#define _SERIAL_HPP_

#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include <cstdint>
#include <fcntl.h>
#include <termios.h>

class Serial{
	private:
		speed_t baud;
		const char* dev;
		int tty_fd_in;
		int tty_fd_out;
		struct termios tio;
		struct termios tio_aux;
	public:
		Serial(const char* dev, speed_t baud);
		~Serial();

		void write(unsigned char* buffer);
		void write(const char* buffer);
		void write(uint8_t* buffer, int length);
		int read(unsigned char* buffer);
		void close();

};
#endif
