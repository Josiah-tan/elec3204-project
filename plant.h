#ifndef PROJECT_PLANT_H
#define PROJECT_PLANT_H


class Plant{
	private:
		int delaytime;
	public:
		Plant(int delaytime = 1000): delaytime(delaytime) {
			
		}
		void setup(){
			pinMode(LED_BUILTIN, OUTPUT);
		}
		void loop(){
			digitalWrite(LED_BUILTIN, HIGH);
			delay(delaytime);
			digitalWrite(LED_BUILTIN, LOW);
			delay(delaytime);
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
