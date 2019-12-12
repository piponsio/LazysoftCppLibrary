#include <lazysoft/storm32_command.hpp>

Storm32_command::Storm32_command(const char* dev = NULL, speed_t baud = B0):size(0),buffer(NULL),com(dev, baud){
}

double* Storm32_command::getAngles(){
	angles[0] = 999.9;
	angles[1] = 999.9;
	angles[2] = 999.9;

	uint16_t pitch;
	uint16_t roll;
	uint16_t yaw;

	this->getDataFields("IMU1ANGLES");

	pitch = (uint16_t) this->buffer[5];
	pitch = pitch | ( (uint16_t)this->buffer[6] << 8);

	this->angles[0] = (pitch > 32767) ? ( (65535 - pitch) / -100.0) : (pitch / 100.0);

	roll = (uint16_t) this->buffer[7];
	roll = roll | ( (uint16_t)this->buffer[8] << 8);

	this->angles[1] = (roll > 32767) ? ( (65535 - roll) / -100.0) : (roll / 100.0);

	yaw = (uint16_t) this->buffer[9];
	yaw = yaw | ( (uint16_t)this->buffer[10] << 8);

	this->angles[2] = (yaw > 32767) ? ( (65535 - yaw) / -100.0) : (yaw / 100.0);

	return this->angles;
}
uint8_t* Storm32_command::listen(uint8_t byte2listen = 0, std::chrono::microseconds max_time = std::chrono::microseconds(10000)){

	this->size = 0;

	std::chrono::microseconds init_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::microseconds now;

	unsigned char init_char = 0xFB;
	bool exit = false;
	if(byte2listen > 0){
		this->size = byte2listen;

		this->buffer = NULL;
		this->buffer = new uint8_t[this->size];
	}


	unsigned char reading;
	uint8_t size = 0;

	while(!exit){

		if(&this->com && this->com.read(&reading) > 0 ){
			if(size > 0) size++;
			if(reading == init_char && size == 0) size = 1;

			if(byte2listen > 0) this->buffer[size-1] = reading;
			if(byte2listen == 0 && size == 2){
				this->size = reading + 5;

				this->buffer = NULL;
				this->buffer = new uint8_t[this->size];
				this->buffer[0] = init_char;
			}
			if(byte2listen == 0 && size >= 2) this->buffer[size-1] = reading;

			if( (this->size > 0) && (size >= this->size) ) exit = true;
		}

		now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
		if((now - init_time) > max_time) exit = true;
	}

	this->time_listen = (now - init_time);

	return this->buffer;
}
uint8_t* Storm32_command::getVersion(){
	this->size = 5;

	this->buffer = NULL;
	this->buffer = new uint8_t[this->size];

	uint8_t prebuffer[] = {0x00, 0x02};
        uint16_t crc = Checksum::crc_calculate(prebuffer,2);

	this->buffer[0] = 0xFA;
	this->buffer[1] = prebuffer[0];
        this->buffer[2] = prebuffer[1];
        this->buffer[3] = (uint8_t)(crc);
        this->buffer[4] = (uint8_t)(crc>>8);

	if(&this->com) this->com.write(this->buffer,this->size);
	if(&this->com) this->listen();

	return this->buffer;
}
uint8_t* Storm32_command::getDataFields(const char* live_data = "STATUS_V2"){
	this->size = 7;

	this->buffer = NULL;
 	this->buffer = new uint8_t[this->size];

	uint8_t prebuffer[4] = {0x02, 0x06, 0x00, 0x20};
	if(strcmp(live_data,"TIMES") == 0){
		prebuffer[2] = 0x02;
		prebuffer[3] = 0x00;
	}
	else if(strcmp(live_data,"IMU1GYRO") == 0){
		prebuffer[2] = 0x04;
		prebuffer[3] = 0x00;
	}
	else if(strcmp(live_data,"IMU1ACC") == 0){
		prebuffer[2] = 0x08;
		prebuffer[3] = 0x00;
	}
	else if(strcmp(live_data,"IMU1R") == 0){
		prebuffer[2] = 0x10;
		prebuffer[3] = 0x00;
	}
	else if(strcmp(live_data,"IMU1ANGLES") == 0){
		prebuffer[2] = 0x20;
		prebuffer[3] = 0x00;
	}
	else if(strcmp(live_data,"PIDCNTRL") == 0){
		prebuffer[2] = 0x40;
		prebuffer[3] = 0x00;
	}
	else if(strcmp(live_data,"INPUTS") == 0){
		prebuffer[2] = 0x80;
		prebuffer[3] = 0x00;
	}
	else if(strcmp(live_data,"IMU2ANGLES") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x01;
	}
	else if(strcmp(live_data,"STATUS_DISPLAY") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x02;
	}
	else if(strcmp(live_data,"STORM32LINK") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x04;
	}
	else if(strcmp(live_data,"IMUACCCONFIDENCE") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x08;
	}
	else if(strcmp(live_data,"ATTITUDE_RELATIVE") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x10;
	}
	else if(strcmp(live_data,"STATUS_V2") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x20;
	}
	else if(strcmp(live_data,"ENCODERANGLES") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x40;
	}
	else if(strcmp(live_data,"IMUACCABS") == 0){
		prebuffer[2] = 0x00;
		prebuffer[3] = 0x80;
	}

        uint16_t crc = Checksum::crc_calculate(prebuffer,4);

        this->buffer[0] = 0xFA;
	this->buffer[1] = prebuffer[0];
        this->buffer[2] = prebuffer[1];
        this->buffer[3] = prebuffer[2];
        this->buffer[4] = prebuffer[3];
        this->buffer[5] = (uint8_t) crc;
        this->buffer[6] = (uint8_t)(crc>>8);

	if(&this->com) this->com.write(this->buffer,this->size);
	if(&this->com) this->listen();

	return this->buffer;
}
//uint8_t* Storm32_command::getDataFields(){
//	return getDataFields("STATUS_V2");
//}
uint8_t* Storm32_command::setAngle(float pitch, float roll, float yaw){
	this->size = 19;

	this->buffer = NULL;
	this->buffer = new uint8_t[this->size];

	uint32_t pitch_temp;
	uint32_t roll_temp;
	uint32_t yaw_temp;

        uint8_t pitch_hex[4];
        uint8_t roll_hex[4];
        uint8_t yaw_hex[4];

        memcpy(&pitch_temp, &pitch, 4);
        memcpy(&roll_temp, &roll, 4);
        memcpy(&yaw_temp, &yaw, 4);

        pitch_hex[0] = pitch_temp;
        pitch_hex[1] = pitch_temp >> 8;
        pitch_hex[2] = pitch_temp >> 16;
        pitch_hex[3] = pitch_temp >> 24;

        roll_hex[0] = roll_temp;
        roll_hex[1] = roll_temp >> 8;
        roll_hex[2] = roll_temp >> 16;
        roll_hex[3] = roll_temp >> 24;

        yaw_hex[0] = yaw_temp;
        yaw_hex[1] = yaw_temp >> 8;
        yaw_hex[2] = yaw_temp >> 16;
        yaw_hex[3] = yaw_temp >> 24;

	uint8_t prebuffer[] = {0x0E, 0x11,
                                pitch_hex[0], pitch_hex[1], pitch_hex[2], pitch_hex[3],
                                roll_hex[0], roll_hex[1], roll_hex[2], roll_hex[3],
                                yaw_hex[0], yaw_hex[1], yaw_hex[2], yaw_hex[3],
                                0x07, 0x00};

        uint16_t crc = Checksum::crc_calculate(prebuffer,16);

	this->buffer[0] = 0xFA;
        this->buffer[1] = prebuffer[0];
        this->buffer[2] = prebuffer[1];
        this->buffer[3] = prebuffer[2];
        this->buffer[4] = prebuffer[3];
        this->buffer[5] = prebuffer[4];
        this->buffer[6] = prebuffer[5];
        this->buffer[7] = prebuffer[6];
        this->buffer[8] = prebuffer[7];
        this->buffer[9] = prebuffer[8];
        this->buffer[10] = prebuffer[9];
        this->buffer[11] = prebuffer[10];
        this->buffer[12] = prebuffer[11];
        this->buffer[13] = prebuffer[12];
        this->buffer[14] = prebuffer[13];
        this->buffer[15] = prebuffer[14];
        this->buffer[16] = prebuffer[15];
        this->buffer[17] = (uint8_t)(crc);
        this->buffer[18] = (uint8_t)(crc >> 8);

	if(&this->com) this->com.write(this->buffer,this->size);
	if(&this->com) this->listen();

	return this->buffer;
}
