#include "coffee_ui.hpp"

CoffeeUi::CoffeeUi(QWidget *parent) : QWidget(parent)
{
	QString drinksList[] = {"The", "Cappuccino", "Caffè Latte", "Caffè Americano"};
	int drinksCount = 4;

	QVBoxLayout *vBox = new QVBoxLayout(this);	
	vBox->setSpacing(1);

	// Connect Button
	QPushButton *initSerialBtn = new QPushButton("Connect", this);
	vBox->addWidget(initSerialBtn);

	// Log Window
	logView = new QLabel(this);	
	logView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	logView->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	logView->setText("Loading ...");

	vBox->addWidget(logView);

	// Drinks Selection Panel
	QGridLayout *drinks = new QGridLayout();
	drinks->setSpacing(1);	
	
	sigMapper = new QSignalMapper(this);

	int y[] = {0, 0, 1, 1};
	for (int i = 0; i < drinksCount; i++) {
		QPushButton *button = new QPushButton(drinksList[i], this);
		connect(button, SIGNAL(clicked()), sigMapper, SLOT(map()));
		sigMapper->setMapping(button, drinksList[i]); 

		drinks->addWidget(button, (i % 2) ? 1 : 0, y[i]);
	}		

	connect(sigMapper, SIGNAL(mapped(QString)), this, SIGNAL(drinkClicked(QString)));

	// 
	vBox->addLayout(drinks);

	setLayout(vBox);
}

CoffeeUi::~CoffeeUi() 
{
	// Do nothing
}

void CoffeeUi::drinkClicked(QString drink)
{
	QMessageBox::information(this, "Button Click", "Drink : " + drink);
}
