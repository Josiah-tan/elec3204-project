#ifndef SERIAL_H
#define SERIAL_H


class SerialDriver{
	/* 
	 * class: serial driver for communication with Python script
	 * parameters:
	 *  -- read_string: string to read in from the serial
	 *  -- real_number: number converted from the string from serial (default = 0)
	 */
	private:
		String read_string;
		int read_number;
	public:
		SerialDriver(int read_number = 0): read_number(read_number){}
		void setup() {
			Serial.begin(115200); // set serial baud rate
			Serial.setTimeout(1); // important for readString();
		}
		void test() {
			/*
			 * wait until serial is available, and then read a string and convert it to an integer before sending it back to serial
			 */
			while (!Serial.available());
			read_string = Serial.readString();
			read_number = read_string.toInt();
			Serial.print(read_string);
		}
		void testSend() {
			/*
			 * print a string to serial
			 */
			Serial.print("testing send");
		}
		void testGUI() {
			/*
			 * code for the testing the GUI: if serial is available, read from the serial, convert to a string, and then print out the reference given
			 */
			if (Serial.available()){
				read_string = Serial.readString();
				read_number = read_string.toInt();
				Serial.print("reference ");
				Serial.println(read_number);
			}
		}
		int getReference() {
			/*
			 * code for obtaining the reference from the serial: if the serial is available, read from the serial, convert to a string, and then return the string 
			 */
			if (Serial.available()){
				read_string = Serial.readString();
				read_number = read_string.toInt();
			}
			return read_number;
		}
};







#endif
