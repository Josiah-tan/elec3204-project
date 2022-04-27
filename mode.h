#ifndef MODE_H
#define MODE_H

#include "plant.h"
#include "pwm.h"
#include "serial.h"
#include "sensor.h"
#include "controller.h"

typedef enum {PWM_TEST, SERIAL_TEST, SPEED_READ_TEST, CLOSED_LOOP_TEST, OPEN_LOOP_TEST, IDLE} MODE;

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
			else if (_mode == CLOSED_LOOP_TEST){
				PWM pwm;
				serial = SerialDriver();
				sensor = Sensor(3, 4);
				controller = Controller(1, 1, 0.01, true);
			}
			else if (_mode == OPEN_LOOP_TEST){
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
			else if (_mode == CLOSED_LOOP_TEST){
				pwm.setup();
				serial.setup();
				sensor.setup();
			}
			else if (_mode == OPEN_LOOP_TEST){
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
				// serial.testSend();
				serial.testGUI();
			}
			else if (_mode == SPEED_READ_TEST){
				// should be anticlockwise
				pwm.set(25);
				// should be clockwise
				// pwm.set(75);
				// PWM_Test::simple();
				sensor.test();
			}
			else if (_mode == CLOSED_LOOP_TEST){
				int reference = serial.getReference();
				int speed = sensor.getSpeed();
				Serial.print("reference: ");
				Serial.println(reference);
				Serial.print("speed: ");
				Serial.println(speed);
				int input = controller.pid(speed, reference);
				// pwm.set(50);
				Serial.print("pwm: ");
				Serial.println(input);
				pwm.set(input);
				// delay(100);
				// delay(1);
				// delay(100);
			}
			else if (_mode == OPEN_LOOP_TEST){
				// assumes that you are sending pwm values, so don't get confused when the initial value is 0, and that causes the motor to spin
				int reference = serial.getReference();
				// int speed = sensor.getSpeed();
				// int input = controller.pid(speed, reference);
				// pwm.set(50);
				pwm.set(reference);
				Serial.println(reference);
			}
		}
};







#endif
