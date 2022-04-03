#ifndef PWM_H
#define PWM_H



class PWM{
	private:
		int delaytime;
	public:
		PWM(int delaytime = 1000): delaytime(delaytime) {
			
		}
		void init(){
			pinMode(LED_BUILTIN, OUTPUT);
		}
		void run(){
			digitalWrite(LED_BUILTIN, HIGH);
			delay(delaytime);
			digitalWrite(LED_BUILTIN, LOW);
			delay(delaytime);
		}
		void test(){
			PWM pwm(10000);
			pwm.init();
			while (true) {
				pwm.run();
			}
		}
		
// void setup() {
// 	pinMode(LED_BUILTIN, OUTPUT);
// }
//
// void loop() {
// 	digitalWrite(LED_BUILTIN, HIGH);
// 	delay(1000);
// 	digitalWrite(LED_BUILTIN, LOW);
// 	delay(1000);
// }
};







#endif
