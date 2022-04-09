
#include "mode.h"

/* Mode mode(SERIAL_TEST); */
/* Mode mode(PWM_TEST); */
Mode mode(SPEED_READ_TEST);
void setup() {
	mode.setup();
}

void loop() {
	mode.loop();
}

