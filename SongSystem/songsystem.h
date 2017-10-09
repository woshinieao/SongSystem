#ifndef SONGSYSTEM_H
#define SONGSYSTEM_H

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include <QString>
#include "ui_songsystem.h"
#include "buymode.h"
#include "salemode.h"
#include "stockmode.h"
#include "sign.h"

typedef enum
{
	PERMISSION_NOBODY,
	PERMISSION_USER,
	PERMISSION_ROOT,

}ePermissonUser;


class SongSystem : public QMainWindow ,public Ui_SongSystemClass
{
	Q_OBJECT

public:
	SongSystem(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SongSystem();

public slots: 
	void SetUserMode();
	void Saleshow();
	void Buyshow();
	void Stockshow();
private:
	//	Ui::SongSystemClass ui;
	ePermissonUser  usermode; 

	Sign signmode;
	SaleMode salemode;
	StockMode stockmode;
	BuyMode buymode;
};

#endif // SONGSYSTEM_H
