#ifndef SALEMODE_H
#define SALEMODE_H

#include <QWidget>
#include "commen.h"
#include "ui_salemode.h"

class SaleMode : public QWidget,public Ui_SaleMode
{
	Q_OBJECT

public:
	SaleMode(QWidget *parent = 0);
	~SaleMode();
	void setDb(db_ops *db){m_db=db;};

private:
	//Ui::SaleMode ui;
	db_ops *m_db;
};

#endif // SALEMODE_H
