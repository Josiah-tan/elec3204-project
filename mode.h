#ifndef MODE_H
#define MODE_H

#include "plant.h"
#include "pwm.h"
#include "serial.h"

typedef enum {PWM_TEST, SERIAL_TEST} MODE;

class Mode{
	private:
		PWM pwm;
		SerialDriver serial;
		MODE _mode;
	public:
		Mode(MODE _mode): _mode(_mode) {
			switch (_mode) {
				case PWM_TEST:
					break;
				case SERIAL_TEST:
					serial = SerialDriver();
					break;
				default:
					break;
			}
		}
		void setup(){
			switch (_mode) {
				case PWM_TEST:
					break;
				case SERIAL_TEST:
					serial.setup();
					break;
				default:
					break;
			}
		}
		void loop(){
			switch (_mode) {
				case PWM_TEST:
					PWM_Test::simple();
					break;
				case SERIAL_TEST:
					serial.test();
				default:
					break;
			}
		}
};







#endif
