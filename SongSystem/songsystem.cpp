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
	connect(&signmode,SIGNAL(sigUser(ePermissonUser)),this,SLOT(SetUserMode(ePermissonUser)));


	

}

void SongSystem::SetUserMode(ePermissonUser user)
{
	usermode = user;
	m_db = db_init_mysql();
	if(m_db == NULL)
	{
		QMessageBox box(QMessageBox::Warning,"����","���ݿ�����ʧ��");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		box.exec();
		exit(-1);
	}
	
	salemode.setDb(m_db);
	buymode.setDb(m_db);
	stockmode.setDb(m_db);
}

void SongSystem::Saleshow()
{
	
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"��ʾ","���ȵ�¼�û���");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		box.exec();
		return ;
	}
}

void SongSystem::Buyshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"��ʾ","���ȵ�¼�û���");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		//box.setButtonText (QMessageBox::Cancel,QString("ȡ ��"));
		box.exec();
		return ;
	}


	buymode.show();




}


void SongSystem::Stockshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"��ʾ","���ȵ�¼�û���");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("ȷ ��"));
		//box.setButtonText (QMessageBox::Cancel,QString("ȡ ��"));
		box.exec();
		return ;
	}
}


SongSystem::~SongSystem()
{

}
