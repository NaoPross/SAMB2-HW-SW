#include <QApplication>
#include "coffee_ui.hpp"

/**************************************************
 * MAIN PROGRAM
 **************************************************/

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	CoffeeUi window;

	window.resize(250, 150);
	window.setWindowTitle("Coffee Machine");
	window.show();

	return app.exec();
}
