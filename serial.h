#ifndef SERIAL_H
#define SERIAL_H


class SerialDriver{
	private:
		int read_string;
	public:
		SerialDriver() {}
		void init() {
			Serial.begin(115200);
			Serial.setTimeout(1);
		}
		void test() {
			while (!Serial.available());
			read_string = Serial.readString().toInt();
			Serial.print(read_string + 1);
		}
};







#endif
