#ifndef STOCKMODE_H
#define STOCKMODE_H

#include <QWidget>
#include "ui_stockmode.h"

class StockMode : public QWidget
{
	Q_OBJECT

public:
	StockMode(QWidget *parent = 0);
	~StockMode();

private:
	Ui::StockMode ui;
};

#endif // STOCKMODE_H
