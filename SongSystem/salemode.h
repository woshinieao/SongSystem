#ifndef SALEMODE_H
#define SALEMODE_H

#include <QDialog>
#include "ui_salemode.h"
#include "commen.h"

class SaleMode : public QDialog,public Ui_SaleMode
{
	Q_OBJECT

public:
	SaleMode(QWidget *parent = 0);
	~SaleMode();
	QString cost_price;
	int m_num;
public slots:
		void Sale();
		void Print();
		void Cancel();
		void clearInfo();
signals:
		void sigSaleBill();
		void sigSaleNum(int);
private:
	
	//Ui::SaleMode ui;
};

#endif // SALEMODE_H
