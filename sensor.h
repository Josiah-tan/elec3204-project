#ifndef SENSOR_H
#define SENSOR_H
#include <limits.h>

/* numerated datatype to denote the direction of the motor (clockwise or anticlockwise) */
typedef enum {CLOCK, ANTI} DIRECTION;

class Sensor{
	/*
	 * class: read information from the encoders to obtain speed and direction
	 * parameters:
	 *  -- pinA and pinB: pins that read a appear of signals 90 degrees out of phase (default: pinA = 3, pinB = 4)
	 *  -- currentA: current state of the pinA
	 *  -- lastA: the last state of the pinA
	 *  -- counter: a counter to approximate position (if needed)
	 *  -- direction: the current direction of the rotation of the motor
	 *  -- last_time: the last time a method was called in this class
	 *  -- period: the period between each method call
	 */
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
			counter = 0; // assume that initial position is 0
			period = ULONG_MAX; // assume initially stationary and hence period is infinite
		}
		void setup() {
			/*
			 * function: setting up pins and variables
			 */
			// set both pins to be inputs
			pinMode(pinA, INPUT);
			pinMode(pinB, INPUT);
			// read the last value of pinA
			lastA = digitalRead(pinA);
			// set the last time to be the current time
			last_time = micros();
		}
		void old() {
			/* method 1: using polling to determine the speed and the rotation of the motor */
			// set the current value of pin A
			currentA = digitalRead(pinA);
			if (currentA != lastA && currentA == 1) { // check if rising edge
				unsigned long current_time = micros();
				period = current_time - last_time; // find the period between the last time that this function was called
				last_time = current_time; // cache the time

				if (digitalRead(pinB) != currentA) { // if B is low, the motor is spinning in theclock wise direction
					counter--;
					direction = CLOCK;
					// Serial.println("clock");
				} else { // otherwise the motor is spinning in the anticlockwise direction
					counter++;
					direction = ANTI;
					// Serial.println("anti");
				}
			}
			lastA = currentA; // cache the last value of A
		}
		void update() {
			/*
			 * method 2: using in built pulseIn to obtain the period between each rising edge
			 * danger: make sure not to put any time consuming code here, like printing to serial
			 */
			period = pulseIn(pinA, HIGH) * 2; // multiply by two to get the actual period (measures the time of a single "pulse", hence rising edge followed by a falling edge, rather than a rising edge, followed by another rising edge)
			if (period == 0){ // the period cannot possibly be zero in a real world sense, however pulseIn returns zero after a time out period (for example if the motor has stopped spinning)
				period = ULONG_MAX; // in this case we set the period to be zero
			}
			if (digitalRead(pinB) != currentA) { // if the state of the pin B is not equal to the current A (just after pulseIn)
				direction = CLOCK; // the direction must be clockwise
				// Serial.println("clock");
			} else {
				direction = ANTI; // else anticlockwise
				// Serial.println("anti");
			}
		}
		void test(){
			/* quick testing of the update function to make sure that the period is being outputted correctly */
			update();
			// Serial.println("testing serial period: ");
			// Serial.print(period);
			// int currentA = digitalRead(pinA);
			// int currentB = digitalRead(pinB);
			// Serial.println("testing current B: ")
			// Serial.println(currentB);
			// Serial.println("testing current A: ")
			// Serial.println(currentA);
		}

		int getSpeed(){
			/* gets the current speed of the motor from the encoder */
			update(); // get the most recent speed
			int speed = 60 / 0.001188 / period; // actual calculation (simplified for efficiency): 60 / (99 * 12 * (period * 10 **-6))
			if (direction == ANTI) { // if the motor is spinning in the anticlockwise direction, set the speed to be negative
				return -speed;
			}
			else {
				return speed;
			}
		}
};







#endif
