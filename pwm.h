#ifndef PWM_H
#define PWM_H



class PWM{
	private:
		int pinB;
		int pinA;
		int current;
	public:
		PWM(int current = 50, int pinA = 9, int pinB = 10): current(current), pinA(pinA), pinB(pinB){

		}
		void setup(){
			pinMode(pinA, OUTPUT);  // set pin A to Q1
			pinMode(pinB, OUTPUT); // set pin B to Q2
			analogWrite(pinA, 0); // let pin A = 0
			analogWrite(pinB, 0); // let pin B = 0
			TCCR1A = 0; // clear Timer1 control register TCCR1A & B
			TCCR1B = 0;
			TCNT1 = 0; // clear Timer1 counter register

			TCCR1B |= _BV(CS11); //set prescaler=8 by lettin the bit value of CS11=1 in register TCCR1B, so the clock frequency=16MHz/8=2MHz
			ICR1 = 100;//  phase correct PWM. PWM frequency determined by counting up 0-100 and counting down 100-0 in the input compare register (ICR1), so freq=200*0.5us=10kHz 
		}
		void loop(){
		}
		int get(){
			return current;
		}
		void set(int pwm){
			current = pwm;
			int temp = (int)pwm;
			temp = constrain(temp,1,99);

			OCR1A = temp; //duty of PWM for pin9 is from output compare register A 
			TCCR1A |= _BV(COM1A1) | _BV(COM1A0); //set output to low level

			OCR1B = temp;//duty of PWM for pin10 is from output compare register B
			TCCR1A |= _BV(COM1B1); //set output to high level

			TCCR1B |= _BV(WGM13); //
			TCCR1A |= _BV(WGM11); //Set ICR1 phas correct mode
		}

};

// class PWM_Test{
// 	public:
//
// 		static void simple() {
// 			PWM pwm;
// 			pwm.setup();
// 			pwm.set(99);
// 			// while (true) {
// 			// 	pwm.set(99); // set duty of pwm as 30%
// 			// 	delay(1000);
// 			// }
// 		}
// };




// 60 / (99 * 12 * (526 * 10 **-6))
// (99 * 12 * (10 **-6))

// frequency from there, divide by 12
// // this the the resolution per second, the revolution per minute multiply by 60 cause by minute, this is the PHO*ERT RPM, gear ratio 99.the result get from here, that frequency, / 12* 60 / 99, and then get the actual value PWM
#endif
