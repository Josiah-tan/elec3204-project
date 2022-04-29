#ifndef MODE_H
#define MODE_H

#include "pwm.h"
#include "serial.h"
#include "sensor.h"
#include "controller.h"

// different modes that can be run
typedef enum {PWM_TEST, SERIAL_TEST, SPEED_READ_TEST, CLOSED_LOOP_TEST, OPEN_LOOP_TEST, PWM_SERIAL_TEST, IDLE} MODE;

class Mode{
	/* class: contains the main code for initialization, setup and looping
	 * parameters:
	 *  -- _mode: which mode should be run (of numerated type "MODE")
	 */
	private:
		PWM pwm;
		SerialDriver serial;
		MODE _mode;
		Sensor sensor;
		Controller controller;
	public:
		Mode(MODE _mode): _mode(_mode) {
			/* constructor: initialization of all objects required for each mode */
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
			else if (_mode == OPEN_LOOP_TEST){
				PWM pwm;
				serial = SerialDriver();
				sensor = Sensor(3, 4);
				controller = Controller(0, 0, 0, true);
			}
			else if (_mode == PWM_SERIAL_TEST){
				PWM pwm;
				serial = SerialDriver();
			}
			else if (_mode == CLOSED_LOOP_TEST){
				PWM pwm;
				serial = SerialDriver();
				sensor = Sensor(3, 4);
				controller = Controller(1, 1, 0.01, true);
			}
		}
		void setup(){
			/* setup: calling the setup function of all objects for each mode (if required) */
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
			else if (_mode == PWM_SERIAL_TEST){
				pwm.setup();
				serial.setup();
			}
			else if (_mode == OPEN_LOOP_TEST){
				pwm.setup();
				serial.setup();
				sensor.setup();
			}
		}
		void loop(){
			/* function: code to run on a loop */
			if (_mode == PWM_TEST){
				// test pwm in both the backward and the forward directions
				pwm.set(99);
				delay(5000);
				pwm.set(1);
				delay(5000);
			}
			else if (_mode == SERIAL_TEST) {
				// try different types of serial testing (see serial.h for more information on the api)
				// serial.test();
				// serial.testSend();
				serial.testGUI();
			}
			else if (_mode == SPEED_READ_TEST){
				// testing the direction and the speed of the motor (see sensor.h for more information on the api)
				// should be anticlockwise
				pwm.set(25);
				// should be clockwise
				// pwm.set(75);
				sensor.test();
			}
			else if (_mode == PWM_SERIAL_TEST){
				// accepts values between [1, 99]
				// assumes that pwm values are being sent, the motor should spin at 0 (the default)
				int reference = serial.getReference();
				pwm.set(reference);
				Serial.println("reference: ");
				Serial.println(reference);
			}
			else if (_mode == CLOSED_LOOP_TEST || _mode == OPEN_LOOP_TEST){
				// accepts values between (-99, 99)
				// implementation of PID control (note that open_loop_test has 0 for the PID constants)
				int reference = serial.getReference();
				int speed = sensor.getSpeed();
				int input = controller.pid(speed, reference);
				pwm.set(input);
				// print values for graphing
				Serial.print("reference: ");
				Serial.println(reference);
				Serial.print("speed: ");
				Serial.println(speed);
				Serial.print("pwm: ");
				Serial.println(input);
			}
		}
};







#endif
