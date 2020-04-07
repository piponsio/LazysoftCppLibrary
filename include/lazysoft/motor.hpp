#ifndef _MOTOR_HPP_
#define _MOTOR_HPP_

#include <wiringPi.h>
#include <softPwm.h>
#include <cstddef>

class Motor{
	private:
		int pin_pwm = 0;
		int pin_cw = 0;
		int pin_ccw = 0;
		int encoder_a = 0;
		int encoder_b = 0;

		int default_pwm = 0;
		int pwm = 0;

		volatile long value = 0;
		volatile int lastEncoded = 0;

		static int countEncoders;
		static Motor** encoders;

		bool sense = true;

		static void updateEncoders();
		void init_pwm(int pwm, bool relative = false);
	public:
		Motor(int pin_pwm, int default_pwm, int pin_cw, int pin_ccw, int encoder_a, int encoder_b, bool sense = true);
		~Motor();

		void cw(int value = 0, int pwm = 0, bool relative = false);
		void ccw(int value = 0, int pwm = 0, bool relative = false);
		void stop();

		volatile long getValue();
		void setValue(volatile long value);
		bool getSense();
		int getPWM();
		int getPinCW();
		int getPinCCW();
};
#endif
