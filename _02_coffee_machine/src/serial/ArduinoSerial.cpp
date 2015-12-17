#include <ArduinoSerial.h>

ArduinoSerial::ArduinoSerial()
{
    // Does nothing
}

int ArduinoSerial::open()
{
	// 0 is clean exit state
	int state = 0;

	serial.Open(ARDUINO_SERIAL_PORT);
    serial.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_9600);
    serial.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
    serial.SetNumOfStopBits(1);
	serial.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
    serial.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);

	if (serial.IsOpen() == false) {
		// Failed to open the serial
		state = 1;
	}

	return state;
}

void ArduinoSerial::close()
{
	serial.Close();
}

std::string ArduinoSerial::read()
{
    std::string buff = "";
    
    // TODO: create a killRead() method
    while (true) {
        char c;
        serial >> c;
        
        if (c == '\n') {
            break;
        }
        else {
            buff += c;
        }
    }
    
	return buff;
}

void ArduinoSerial::write(std::string msg)
{
    serial << msg;
}
