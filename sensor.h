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
			last_time = micros();
		}
		void update() {
			currentA = digitalRead(pinA);
			// Serial.println(digitalRead(pinB));

			if (currentA != lastA && currentA == 1) {
				unsigned long current_time = micros();
				period = current_time - last_time;
				last_time = current_time;

				if (digitalRead(pinB) != currentA) {
					counter--;
					direction = CLOCK;
					// Serial.println("clock");
				} else {
					counter++;
					direction = ANTI;
					// Serial.println("anti");
				}
			}
			lastA = currentA;
		}
		void test(){
			update();
			// Serial.println("hello whorl");
			// Serial.print(period);
			// int currentA = digitalRead(pinA);
			// int currentB = digitalRead(pinB);
			// Serial.println(currentB);
			// Serial.println(currentA);
		}
		
		int getSpeed(){
			update();
			// 60 / (99 * 12 * (period * 10 **-6))
			int speed = 60 / 0.001188 / period;
			if (ANTI) {
				return -speed;
			}
			else {
				return speed;
			}
		}
};







#endif
