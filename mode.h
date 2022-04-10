#ifndef MODE_H
#define MODE_H

#include "plant.h"
#include "pwm.h"
#include "serial.h"
#include "sensor.h"
#include "controller.h"

typedef enum {PWM_TEST, SERIAL_TEST, SPEED_READ_TEST, PLANT_TEST, IDLE} MODE;

class Mode{
	private:
		PWM pwm;
		SerialDriver serial;
		MODE _mode;
		Sensor sensor;
		Controller controller;
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
			else if (_mode == PLANT_TEST){
				PWM pwm;
				serial = SerialDriver();
				sensor = Sensor(3, 4);
				controller = Controller(1, 0, 0, true);
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
			else if (_mode == PLANT_TEST){
				pwm.setup();
				serial.setup();
				sensor.setup();
			}
		}
		void loop(){
			if (_mode == PWM_TEST){
				pwm.set(99);
				delay(5000);
				pwm.set(1);
				delay(5000);
				// PWM_Test::simple();
			}
			else if (_mode == SERIAL_TEST) {
				// serial.test();
				serial.testSend();
			}
			else if (_mode == SPEED_READ_TEST){
				// should be anticlockwise
				pwm.set(25);
				// should be clockwise
				// pwm.set(75);
				// PWM_Test::simple();
				sensor.test();
			}
			else if (_mode == PLANT_TEST){
				int reference = serial.getReference();
				int speed = sensor.getSpeed();
				int input = controller.pid(speed, reference);
				// pwm.set(50);
				pwm.set(input);
			}
		}
};







#endif
