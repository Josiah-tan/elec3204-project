#ifndef SENSOR_H
#define SENSOR_H
#include <limits.h>

typedef enum {CLOCK, ANTI} DIRECTION;

class Sensor{
	private:
		int pinA;
		int pinB;
		int currentA;
		int lastA;
		int counter;
		DIRECTION direction;
		unsigned long last_time;
		unsigned long period;

	public:
		Sensor(int pinA = 3, int pinB = 4): pinA(pinA), pinB(pinB) {
			counter = 0;
			period = ULONG_MAX;
		}
		void setup() {
			pinMode(pinA, INPUT);
			pinMode(pinB, INPUT);
			lastA = digitalRead(pinA);
			last_time = millis();
		}
		void loop() {
			currentA = digitalRead(pinA);
			// Serial.println(digitalRead(pinB));

			if (currentA != lastA && currentA == 1) {
				unsigned long current_time = micros();
				period = current_time - last_time;
				last_time = current_time;
				Serial.println(period);

				if (digitalRead(pinB) != currentA) {
					counter --;
					direction = CLOCK;
				}
				else {
					counter ++;
					direction = ANTI;
				}
			}
			lastA = currentA;
		}
		void test(){
			loop();
			// Serial.println("hello whorl");
			// Serial.print(period);
			// int currentA = digitalRead(pinA);
			// int currentB = digitalRead(pinB);
			// Serial.println(currentB);
			// Serial.println(currentA);
		}
};







#endif
