#include "songsystem.h"

SongSystem::SongSystem(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setupUi(this);
	usermode = PERMISSION_NOBODY;
/*�ⷢ�ź�*/
	connect(btnLogin,SIGNAL(clicked()),&signmode,SLOT(show()));
	connect(btnSale,SIGNAL(clicked()),this,SLOT(Saleshow()));
	connect(btnBuy,SIGNAL(clicked()),this,SLOT(Buyshow()));
	connect(btnStock,SIGNAL(clicked()),this,SLOT(Stockshow()));


/*�����ź�*/
	connect(signmode.btnLogin,SIGNAL(clicked()),this,SLOT(SetUserMode()));

}

void SongSystem::SetUserMode()
{
	

}

void SongSystem::Saleshow()
{
	
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"����","���ȵ�¼�û���");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		box.setButtonText (QMessageBox::Cancel,QString("ȡ ��"));
		box.exec();
		return ;
	}
}

void SongSystem::Buyshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"����","���ȵ�¼�û���");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		box.setButtonText (QMessageBox::Cancel,QString("ȡ ��"));
		box.exec();
		return ;
	}




}


void SongSystem::Stockshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"����","���ȵ�¼�û���");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		box.setButtonText (QMessageBox::Cancel,QString("ȡ ��"));
		box.exec();
		return ;
	}
}


SongSystem::~SongSystem()
{

}
