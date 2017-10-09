#ifndef STOCKMODE_H
#define STOCKMODE_H

#include <QWidget>
#include "ui_stockmode.h"
#include "commen.h"
class StockMode : public QWidget,public Ui_StockMode
{
	Q_OBJECT

public:
	StockMode(QWidget *parent = 0);
	~StockMode();
	void setDb(db_ops *db){m_db=db;};
private:
	//Ui::StockMode ui;
	db_ops *m_db;
};

#endif // STOCKMODE_H
