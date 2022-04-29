#ifndef PWM_H
#define PWM_H



class PWM{
	/*
	 * class: sets the pwm signal for a motor
	 * current: current pwm value, ranges from [1, 99] -- 1 = maximum anticlockwise, and 99 = maximum clockwise (default = 50)
	 * pinA, pinB: produces a complementary pair of pwm signals (default: pinA = 9, pinB = 10)
	 */
	private:
		int pinB;
		int pinA;
		int current;
	public:
		PWM(int current = 50, int pinA = 9, int pinB = 10): current(current), pinA(pinA), pinB(pinB){}
		void setup(){
			/* setup pwm registers */
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
		/* function: does nothing */
		}
		int get(){
			/* function: returns the current pwm value */
			return current;
		}
		void set(int pwm){
			/* function: sets a pwm signal to the motor
			 * parameters:
			 *  -- pwm range between: [1, 99]
			 */
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

#endif
