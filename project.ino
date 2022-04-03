
#include "mode.h"

Mode mode(SERIAL_TEST);
void setup() {
	mode.init();
}

void loop() {
	mode.run();
}
