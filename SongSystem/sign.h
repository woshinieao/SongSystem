#ifndef SIGN_H
#define SIGN_H

#include <QWidget>
#include <QString>
#include "ui_sign.h"

class Sign : public QWidget,public Ui_Sign
{
	Q_OBJECT

public:
	Sign(QWidget *parent = 0);
	~Sign();

	QString user;
	Qstring passwd;

public slots:
		void Signshow();

signals:
		void sigLogin(QString ,QString);
private:
	//Ui::Sign ui;
};

#endif // SIGN_H
