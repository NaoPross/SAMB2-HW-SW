#ifndef __COFFEE_UI_HPP_
#define __COFFEE_UI_HPP_

#include <QWidget>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

#include <QPushButton>
#include <QLabel>

// Serial Library
#include <arduino-serial-lib.h>

class CoffeeUi : public QWidget
{
Q_OBJECT
public:
	CoffeeUi(QWidget *parent = 0);
	~CoffeeUi();

private slots:
	void drinkClicked(QString);

private:
	QSignalMapper *sigMapper;
	QLabel *logView;

};

#endif
