#ifndef __ARDUINOSERIAL_H_
#define __ARDUINOSERIAL_H

#include <SerialStream.h>
#include <SerialPort.h>

#define ARDUINO_SERIAL_PORT "/dev/ttyACM0"
#define BUFFER_SIZE 256

/**************************************************
 * ARDUINO SERIAL COMUNICATION CLASS 
 **************************************************/

class ArduinoSerial
{
public:
	ArduinoSerial();
	
	int open();
	void close();
	
    std::string read();
	void write(std::string msg);

private:
    SerialPort serial;
    //LibSerial::SerialStream serial;
};

#endif
