#include "songsystem.h"

SongSystem::SongSystem(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setupUi(this);
	usermode = PERMISSION_NOBODY;
/*外发信号*/
	connect(btnLogin,SIGNAL(clicked()),&signmode,SLOT(show()));
	connect(btnSale,SIGNAL(clicked()),this,SLOT(Saleshow()));
	connect(btnBuy,SIGNAL(clicked()),this,SLOT(Buyshow()));
	connect(btnStock,SIGNAL(clicked()),this,SLOT(Stockshow()));


/*回收信号*/
	connect(signmode.btnLogin,SIGNAL(clicked()),this,SLOT(SetUserMode()));

}

void SongSystem::SetUserMode()
{
	

}

void SongSystem::Saleshow()
{
	
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"标题","请先登录用户！");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.setButtonText (QMessageBox::Cancel,QString("取 消"));
		box.exec();
		return ;
	}
}

void SongSystem::Buyshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"标题","请先登录用户！");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.setButtonText (QMessageBox::Cancel,QString("取 消"));
		box.exec();
		return ;
	}




}


void SongSystem::Stockshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"标题","请先登录用户！");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.setButtonText (QMessageBox::Cancel,QString("取 消"));
		box.exec();
		return ;
	}
}


SongSystem::~SongSystem()
{

}
