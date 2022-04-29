
#include "mode.h"

// Mode mode(SERIAL_TEST); // test if the serial is working
// Mode mode(PWM_TEST); // test if the pwm output is working
// Mode mode(SPEED_READ_TEST); // test if the speed reading (sensor) is working
Mode mode(CLOSED_LOOP_TEST); // test if the closed loop system is working
// Mode mode(OPEN_LOOP_TEST); // test if the open loop system is working
// Mode mode(PWM_SERIAL_TEST); // test if the pwm combined with serial is working
// Mode mode(IDLE); // set to idle (do nothing)
void setup() {
	mode.setup();
}

void loop() {
	mode.loop();
}

