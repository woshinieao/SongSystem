#ifndef BUYMODE_H
#define BUYMODE_H

#include <QWidget>
#include "ui_buymode.h"
#include "commen.h"
class BuyMode : public QWidget,public Ui_BuyMode
{
	Q_OBJECT

public:
	BuyMode(QWidget *parent = 0);
	~BuyMode();
	void setDb(db_ops *db){m_db=db;};
private:
	//Ui::BuyMode ui;
	db_ops *m_db;
};

#endif // BUYMODE_H
