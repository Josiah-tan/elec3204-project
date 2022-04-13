
#include "mode.h"

/* Mode mode(SERIAL_TEST); */
/* Mode mode(PWM_TEST); */
/* Mode mode(SPEED_READ_TEST); */
/* Mode mode(CLOSED_LOOP_TEST); */
Mode mode(OPEN_LOOP_TEST);
/* Mode mode(IDLE); */
void setup() {
	mode.setup();
}

void loop() {
	mode.loop();
}

