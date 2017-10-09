#ifndef SALEMODE_H
#define SALEMODE_H

#include <QWidget>
#include "ui_salemode.h"

class SaleMode : public QWidget
{
	Q_OBJECT

public:
	SaleMode(QWidget *parent = 0);
	~SaleMode();

private:
	Ui::SaleMode ui;
};

#endif // SALEMODE_H
