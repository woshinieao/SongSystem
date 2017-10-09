#ifndef BUYMODE_H
#define BUYMODE_H

#include <QWidget>
#include "ui_buymode.h"

class BuyMode : public QWidget
{
	Q_OBJECT

public:
	BuyMode(QWidget *parent = 0);
	~BuyMode();

private:
	Ui::BuyMode ui;
};

#endif // BUYMODE_H
