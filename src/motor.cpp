#include <lazysoft/motor.hpp>

int Motor::countEncoders = 0;
Motor** Motor::encoders = NULL;

Motor::Motor(int pin_pwm, int default_pwm, int pin_cw, int pin_ccw, int encoder_a, int encoder_b, bool sense){
    	wiringPiSetup();
	softPwmCreate(pin_pwm, 0, 100);

	pinMode(pin_cw, OUTPUT);
	pinMode(pin_ccw, OUTPUT);

	pinMode(encoder_a, INPUT);
	pinMode(encoder_b, INPUT);

	digitalWrite(pin_cw, LOW);
	digitalWrite(pin_ccw, LOW);

	Motor* temp[Motor::countEncoders];

	if(Motor::encoders != NULL && Motor::countEncoders > 0){
		for(int i = 0; i < Motor::countEncoders; i++) temp[i] = Motor::encoders[i];
		delete [] Motor::encoders;
		Motor::encoders = NULL;
	}
	Motor::encoders = new Motor*[Motor::countEncoders + 1];

	if(Motor::encoders != NULL && Motor::countEncoders > 0){
		for(int i = 0; i < Motor::countEncoders; i++) Motor::encoders[i] = temp[i];
	}

	Motor::encoders[Motor::countEncoders] = this;
	Motor::countEncoders+=1;

	this->default_pwm = default_pwm;
	this->pin_pwm = pin_pwm;
	this->pin_cw = pin_cw;
	this->pin_ccw = pin_ccw;
 	this->encoder_a = encoder_a;
	this->encoder_b = encoder_b;
	this->sense = sense;

	pinMode(encoder_a, INPUT);
    	pinMode(encoder_b, INPUT);

	pullUpDnControl(encoder_a, PUD_UP);
    	pullUpDnControl(encoder_b, PUD_UP);

	wiringPiISR(encoder_a, INT_EDGE_BOTH, Motor::updateEncoders);
    	wiringPiISR(encoder_b, INT_EDGE_BOTH, Motor::updateEncoders);
}

Motor::~Motor(){
	for (int encoder = 0; encoder < Motor::countEncoders; encoder++){
		if(Motor::encoders[encoder] == this){
			if(encoder < Motor::countEncoders-1) Motor::encoders[encoder] = Motor::encoders[encoder+1];
			else Motor::encoders[encoder] = NULL;
			Motor::countEncoders -= 1;
		}
	}
}

void Motor::cw(int value, int pwm, bool relative){
	this->init_pwm(pwm, relative);

	if( (value > 0 && this->value < value) || (value < 0 && this->value > value)){
		digitalWrite(pin_cw, HIGH);
                digitalWrite(pin_ccw, LOW);
	}
	else this->stop();
}
void Motor::ccw(int value, int pwm, bool relative){
	this->init_pwm(pwm, relative);

	if( (value > 0 && this->value < value) || (value < 0 && this->value > value)){
		digitalWrite(pin_cw, LOW);
                digitalWrite(pin_ccw, HIGH);
	}
	else this->stop();
}
void Motor::stop(){
	digitalWrite(this->pin_cw, LOW);
        digitalWrite(this->pin_ccw, LOW);
	softPwmWrite(this->pin_pwm, 0);
	this->pwm = 0;
}
volatile long Motor::getValue(){
	return this->value;
}
void Motor::setValue(volatile long value){
	this->value = value;
}
bool Motor::getSense(){
	return this->sense;
}
int Motor::getPWM(){
	return this->pwm;
}
int Motor::getPinCW(){
	return this->pin_cw;
}
int Motor::getPinCCW(){
	return this->pin_ccw;
}
void Motor::updateEncoders(){

	unsigned int lastUpdate = 0;
    	unsigned int now = micros();
    	if(lastUpdate - now < 100) {return;}
    	lastUpdate = now;
	for (int encoder = 0; encoder < Motor::countEncoders; encoder++){
		if(Motor::encoders[encoder] != NULL){

			int status_cw = digitalRead((*Motor::encoders[encoder]).pin_cw);
			int status_ccw = digitalRead((*Motor::encoders[encoder]).pin_ccw);

			int MSB = digitalRead((*Motor::encoders[encoder]).encoder_a);
        		int LSB = digitalRead((*Motor::encoders[encoder]).encoder_b);

		        int encoded = (MSB << 1) | LSB;

		 	int sum = ((*Motor::encoders[encoder]).lastEncoded << 2) | encoded;

	        	if((*Motor::encoders[encoder]).encoder_a != 0 && (*Motor::encoders[encoder]).encoder_b != 0){
				if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) (*Motor::encoders[encoder]).value-=1;
	        		if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) (*Motor::encoders[encoder]).value+=1;
			}
			else{
	        		if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000){
					if( (*Motor::encoders[encoder]).getSense() && (status_cw == 1 && status_ccw == 0)) (*Motor::encoders[encoder]).value += 4;
					if( (*Motor::encoders[encoder]).getSense() && (status_cw == 0 && status_ccw == 1)) (*Motor::encoders[encoder]).value -= 4;
					if(!(*Motor::encoders[encoder]).getSense() && (status_cw == 1 && status_ccw == 0)) (*Motor::encoders[encoder]).value -= 4;
					if(!(*Motor::encoders[encoder]).getSense() && (status_cw == 0 && status_ccw == 1)) (*Motor::encoders[encoder]).value += 4;
				}
			}
	        	(*Motor::encoders[encoder]).lastEncoded = encoded;

		}
    	}
}
void Motor::init_pwm(int pwm, bool relative){
	pwm = (relative)? pwm + this->default_pwm : pwm;
	if(pwm == 0) pwm = this->default_pwm;
	if(this->pwm == 0) softPwmWrite(this->pin_pwm, pwm);
	this->pwm = pwm;
}
