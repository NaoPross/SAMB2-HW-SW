// QtLibs
#include <QApplication>
#include <QWidget>

#include <iostream>
#include <string>

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
