#ifndef BUYMODE_H
#define BUYMODE_H

#include <QWidget>
#include "ui_buymode.h"
#include "commen.h"
//#include "combox.h"
class BuyMode : public QWidget,public Ui_BuyMode
{
	Q_OBJECT

public:
	BuyMode(QWidget *parent = 0);
	~BuyMode();
	void setDb(db_ops *db){m_db=db;};
	void InitTypeList(QList<tParam> *brand,QList<tParam> *func,QList<tParam> *type  );


public slots:
	void AddType();
	void DelType();
	void TypeChangeShow(int);
	void Inbound();
	void InboundCancel();
private:
	//Ui::BuyMode ui;
	db_ops *m_db;
	QComboBox comboxbrandList[10];
	QComboBox comboxfunctionList[10];
	QComboBox comboxtypeList[10];

	QList<tParam> *brandList;
	QList<tParam> *functionList;
	QList<tParam> *typeList;
	
};

#endif // BUYMODE_H
