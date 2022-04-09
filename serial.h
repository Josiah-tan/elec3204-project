#ifndef SERIAL_H
#define SERIAL_H


class SerialDriver{
	private:
		String read_string;
		int read_number;
	public:
		SerialDriver() {}
		void setup() {
			Serial.begin(115200);
			// Serial.begin(2000000);
			Serial.setTimeout(1);
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
};







#endif
