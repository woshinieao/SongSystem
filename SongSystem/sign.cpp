#include "sign.h"
#include <QMessageBox>
Sign::Sign(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

		connect(btnLogin,SIGNAL(clicked()),this,SLOT(SignInshow()));
		connect(btnLogout,SIGNAL(clicked()),this,SLOT(SignOutshow()));

}



void Sign::SignInshow()
{
	user = leUser->text();
	passwd = lePasswd->text();
	if(user.compare("root")==0 && passwd.compare("root")==0)
	{
		emit sigUser(PERMISSION_ROOT);
		hide();
	}
	else if(user.compare("admin")==0 && passwd.compare("admin")==0)
	{
		emit sigUser(PERMISSION_USER);
		hide();
	}
	else 	
	{
		QMessageBox box(QMessageBox::Warning,"����","�û������������ ��");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		box.setButtonText (QMessageBox::Cancel,QString("ȡ ��"));
		box.exec();
		lePasswd->clear();
		return ;
	}



}

void Sign::SignOutshow()
{
	leUser->clear();
	lePasswd->clear();
	emit sigUser(PERMISSION_NOBODY);
	

}


Sign::~Sign()
{

}
