#ifndef SONGSYSTEM_H
#define SONGSYSTEM_H

#include <QtGui/QMainWindow>
#include "commen.h"
#include "ui_songsystem.h"
#include "buymode.h"
#include "salemode.h"
#include "stockmode.h"
#include "sign.h"




class SongSystem : public QMainWindow ,public Ui_SongSystemClass
{
	Q_OBJECT

public:
	SongSystem(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SongSystem();


public slots: 
	void SetUserMode(int);
	void SaleListshow();
	void Buyshow();
	void Stockshow();
private:
	//	Ui::SongSystemClass ui;

	void InitDb();

	int  usermode; 
	Sign signmode;
	
	StockMode stockmode;
	BuyMode buymode;
	db_ops *m_db;
	
	QList<tParam> brandList;
	QList<tParam> functionList;
	QList<tParam> typeList;

};

#endif // SONGSYSTEM_H
