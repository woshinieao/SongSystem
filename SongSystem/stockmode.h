#ifndef STOCKMODE_H
#define STOCKMODE_H

#include <QWidget>
#include "ui_stockmode.h"
#include "commen.h"
#include "salemode.h"

#define	CHECK_BRAN 0x0001
#define	CHECK_FUNC 0x0010
#define	CHECK_TYPE 0x0100
#define CHECK_TIME 0x1000

class StockMode : public QWidget,public Ui_StockMode
{
	Q_OBJECT

public:
	StockMode(QWidget *parent = 0);
	~StockMode();
	void setDb(db_ops *db){m_db=db;};
	void InitTypeList(QList<tParam> *brand,QList<tParam> *func,QList<tParam> *type  );
	void setShowMode(int);
	void QuerySale();
	void QueryStock();
public slots:
		
	void Query();
	void Clear();
	void BrandCheckChange();
	void FunctionCheckChange();
	void TypeCheckChange();
	void SelectSaleRow();
	void ProductNumUpdate(int num);
private:
	//Ui::StockMode ui;
	db_ops *m_db;
	QList<tParam> *brandList;
	QList<tParam> *functionList;
	QList<tParam> *typeList;
	SaleMode salemode;
	int m_mode;
};

#endif // STOCKMODE_H
