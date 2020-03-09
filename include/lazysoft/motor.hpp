#ifndef _MOTOR_HPP_
#define _MOTOR_HPP_

#include <wiringPi.h>
#include <softPwm.h>
#include <cstddef>
class Motor{
	public:
//		static const int maxEncoders = 4;
		static int countEncoders;
//		static Motor* encoders[maxEncoders];
		static Motor** encoders;
		bool sense = true;
		int default_pwm = 0;
		int pwm = 0;
		int pin_pwm = 0;
		int pin_cw = 0;
		int pin_ccw = 0;

		int encoder_a = 0;
		int encoder_b = 0;
		volatile long value = 0;
		volatile int lastEncoded = 0;
		//unsigned int lastUpdate = 0;
		Motor();
		Motor(int pin_pwm, int default_pwm, int pin_cw, int pin_ccw, int encoder_a, int encoder_b, bool sense = true);
		void cw(int value = 0, int pwm = 0, bool relative = false);
		void ccw(int value = 0, int pwm = 0, bool relative = false);
		void stop();
		void init_pwm(int pwm, bool relative = false);
		~Motor();
		static void updateEncoders();
};
#endif
