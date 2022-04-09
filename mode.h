#ifndef MODE_H
#define MODE_H

#include "plant.h"
#include "pwm.h"
#include "serial.h"
#include "sensor.h"

typedef enum {PWM_TEST, SERIAL_TEST, SPEED_READ_TEST} MODE;

class Mode{
	private:
		PWM pwm;
		SerialDriver serial;
		MODE _mode;
		Sensor sensor;
	public:
		Mode(MODE _mode): _mode(_mode) {
			if (_mode == PWM_TEST){
					PWM pwm;
			}
			else if (_mode == SERIAL_TEST) {
				serial = SerialDriver();
			}
			else if (_mode == SPEED_READ_TEST){
					PWM pwm;
					serial = SerialDriver();
					sensor = Sensor(3, 4);
			}
		}
		void setup(){
			if (_mode == PWM_TEST){
					pwm.setup();
			}
			else if (_mode == SERIAL_TEST) {
					serial.setup();
			}
			else if (_mode == SPEED_READ_TEST){
					pwm.setup();
					serial.setup();
					sensor.setup();
			}
		}
		void loop(){
			if (_mode == PWM_TEST){
					pwm.set(99);
					// PWM_Test::simple();
			}
			else if (_mode == SERIAL_TEST) {
					// serial.test();
					serial.testSend();
			}
			else if (_mode == SPEED_READ_TEST){
					pwm.set(75);
					// PWM_Test::simple();
					sensor.test();
			}
		}
};







#endif
