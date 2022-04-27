#ifndef SERIAL_H
#define SERIAL_H


class SerialDriver{
	private:
		String read_string;
		int read_number;
	public:
		SerialDriver(int read_number = 0): read_number(read_number){}
		void setup() {
			Serial.begin(115200);
			// Serial.begin(2000000);
			Serial.setTimeout(1); // important for readString();
		}
		void test() {
			while (!Serial.available());
			read_string = Serial.readString();
			read_number = read_string.toInt();
			Serial.print(read_string);
		}
		void testSend() {
			Serial.print("hello world");
		}
		void testGUI() {
			if (Serial.available()){
				read_string = Serial.readString();
				read_number = read_string.toInt();
				Serial.print("reference ");
				Serial.println(read_number);
				// Serial.print(read_string);
			}
		}
		int getReference() {
			if (Serial.available()){
				read_string = Serial.readString();
				read_number = read_string.toInt();
				Serial.println(read_string);
			}
			return read_number;
		}
};







#endif
