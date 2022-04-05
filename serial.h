#ifndef SERIAL_H
#define SERIAL_H


class SerialDriver{
	private:
		int read_string;
	public:
		SerialDriver() {}
		void setup() {
			Serial.begin(115200);
			Serial.setTimeout(1);
		}
		void test() {
			while (!Serial.available());
			String read_string = Serial.readString();
			Serial.print(read_string);
		}
};







#endif
