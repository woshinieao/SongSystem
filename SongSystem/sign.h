#ifndef SIGN_H
#define SIGN_H

#include <QWidget>
#include <QString>
#include "ui_sign.h"
#include "commen.h"



class Sign : public QWidget,public Ui_Sign
{
	Q_OBJECT

public:
	Sign(QWidget *parent = 0);
	~Sign();
	QString user;
	QString passwd;

public slots:
		void SignInshow();
		void SignOutshow();
signals:
		void sigUser(ePermissonUser);
private:
	//Ui::Sign ui;
};

#endif // SIGN_H
