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
		QMessageBox box(QMessageBox::Warning,"标题","用户名或密码错误 ！");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.setButtonText (QMessageBox::Cancel,QString("取 消"));
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
