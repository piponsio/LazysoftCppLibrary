#include <lazysoft/serial.hpp>

Serial::Serial(const char* dev = NULL, speed_t baud = B0){
	this->dev = dev;
	this->baud = baud;

        memset(&tio, 0, sizeof(this->tio));
        this->tio.c_iflag=0;
        this->tio.c_oflag=0;
        this->tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more in$
	this->tio.c_lflag=0;
        this->tio.c_cc[VMIN]=1;
        this->tio.c_cc[VTIME]=5;

	if(strcmp(dev,"stdio") == 0){

	        tcgetattr(STDOUT_FILENO,&this->tio_aux);

		this->tio.c_cflag=0;
        	this->tio.c_cc[VTIME]=0;

	        tcsetattr(STDOUT_FILENO,TCSANOW,&this->tio);
	        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&this->tio);
	        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blo$
		this->tty_fd_in = STDIN_FILENO;
		this->tty_fd_out = STDOUT_FILENO;
	}
	else{
 		int tty_fd = open(dev, O_RDWR | O_NONBLOCK);

	        this->tty_fd_in = tty_fd;
	        this->tty_fd_out = tty_fd;
		cfsetospeed(&this->tio, baud);
	        cfsetispeed(&this->tio, baud);
	        tcsetattr(tty_fd,TCSANOW,&this->tio);
	}
}
Serial::~Serial(){
	close();
}
void Serial::write(unsigned char* buffer){
	::write(this->tty_fd_out, buffer, 1);
}
void Serial::write(const char* buffer){
	::write(this->tty_fd_out, buffer, strlen(buffer));
}
void Serial::write(uint8_t* buffer, int length){
	::write(this->tty_fd_out, buffer, length);
}
int Serial::read(unsigned char* buffer){
	return ::read(this->tty_fd_in, buffer, 1);
}
void Serial::close(){
	if(strcmp(this->dev,"stdio") == 0) tcsetattr(this->tty_fd_out,TCSANOW, &this->tio_aux);
	else ::close(this->tty_fd_out);
}
