// Serial
#include <SerialStream.h>
#include <SerialStreamBuf.h>
#include <SerialPort.h>

#define ARDUINO_SERIAL_PORT "/dev/ttyACM0"

// Application
#include <QApplication>
#include <QWidget>

// Generic
#include <string>

/**************************************************
 * ARDUINO SERIAL COMUNICATION CLASS DEFINITION
 **************************************************/

class Arduino
{
public:
	Arduino();
	
	int open();
	void close();
	
	DataBuffer read();
	void write(string msg);

private:
	SerialPort serial;
}

Arduino::Arduino()
{
	serial(ARDUINO_SERIAL_PORT);
}

int Arduino::open()
{
	// 0 is clean exit state
	int state = 0;

	serial.Open(SerialPort::BAUD_9600,
				SerialPort::CHAR_SIZE_8,
				SerialPort::PARITY_NONE,
				SerialPort::STOP_BITS_1,
				SerialPort::FLOW_CONTROL_NONE);

	if (serial.isOpen() == false) {
		// Failed to open the serial
		state = 1;
	}

	return state;
}

void Arduino::close()
{
	serial.Close();
}

DataBuffer Arduino::read()
{
	SerialPort::DataBuffer buff;
	serial.Read(buff, 10, 1000);

	return buff;
}

void Arduino::write(string msg)
{
	serial.write(msg.c_str(), msg.lenght());
}

/**************************************************
 * MAIN PROGRAM
 **************************************************/

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	QWidget window;

	window.resize(250, 150);
	window.setWindowTitle("Coffee Machine");
	window.show();

	return application.exec();
}
