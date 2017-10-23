#include "songsystem.h"

SongSystem::SongSystem(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setupUi(this);
	usermode = PERMISSION_NOBODY;
	usermode =PERMISSION_ROOT;
/*外发信号*/
	connect(btnLogin,SIGNAL(clicked()),&signmode,SLOT(show()));
	connect(btnSale,SIGNAL(clicked()),this,SLOT(SaleListshow()));
	connect(btnBuy,SIGNAL(clicked()),this,SLOT(Buyshow()));
	connect(btnStock,SIGNAL(clicked()),this,SLOT(Stockshow()));
	m_db = NULL;

/*回收信号*/
	connect(&signmode,SIGNAL(sigUser(ePermissonUser)),this,SLOT(SetUserMode(ePermissonUser)));

	//connect(buymode.btnBrand,SIGNAL(clicked()),this,SLOT(SetUserMode(ePermissonUser)));
	

}

void SongSystem::SetUserMode(ePermissonUser user)
{
	usermode = user;
	//InitDb();
}

void SongSystem::SaleListshow()
{
	
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"提示","请先登录用户！");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.exec();
		return ;
	}
	
	InitDb();
	stockmode.setShowMode(SALE_SHOW);
	stockmode.show();
}

void SongSystem::Buyshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"提示","请先登录用户！");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		//box.setButtonText (QMessageBox::Cancel,QString("取 消"));
		box.exec();
		return ;
	}
	InitDb();
	buymode.deTime->setDateTime(QDateTime::currentDateTime());
	buymode.show();


}


void SongSystem::Stockshow()
{
	if(usermode == PERMISSION_NOBODY)
	{
		QMessageBox box(QMessageBox::Warning,"提示","请先登录用户！");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		//box.setButtonText (QMessageBox::Cancel,QString("取 消"));
		box.exec();
		return ;
	}

	InitDb();
	stockmode.setShowMode(STOCK_SHOW);
	stockmode.show();
}



void SongSystem::InitDb()
{

	if(m_db != NULL)
		return ;
	m_db = 	db_init();
	if(m_db == NULL)
	{
		QMessageBox box(QMessageBox::Warning,"错误","数据库连接失败");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.exec();
		exit(-1);
	}
	
	
	buymode.setDb(m_db);
	stockmode.setDb(m_db);


	void *result;
	char **row;
	int iRow = 0;
	char sql[256]={0};
	int num=0;
	int id=0;
	

	sprintf(sql,"select id,brand_name from table_brand_list order by id asc;");
	result = db_getfirst(sql);
	while (result)
	{		
		row   = (char **)result;
		iRow  = 0;

		do
		{
			tParam param;
			/*id*/
			if(row[iRow] == NULL)
				break;
			param.id = atoi(row[iRow]);
			iRow++;

			if(row[iRow] == NULL)
				break;
			param.type = row[iRow];
			brandList.insert(num,param);
			iRow++;
			num++;
			result = db_getnext();
		}while(0);
	}

	id=0;
	num=0;
	memset(sql,0,256);
	sprintf(sql,"select id,function_name from table_function_list order by id asc;");
	result = db_getfirst(sql);
	while (result)
	{		
		row   = (char **)result;
		iRow  = 0;

		do
		{
			tParam param;
			/*id*/
			if(row[iRow] == NULL)
				break;
			param.id = atoi(row[iRow]);
			iRow++;

			if(row[iRow] == NULL)
				break;

			param.type = row[iRow];
			functionList.insert(num,param);
			iRow++;
			num++;
			result = db_getnext();
		}while(0);
	}

	id=0;
	num=0;
	memset(sql,0,256);
	sprintf(sql,"select id,type_name from table_type_list order by id asc;");
	result = db_getfirst(sql);
	while (result)
	{		
		row   = (char **)result;
		iRow  = 0;

		do
		{
				tParam param;
			/*id*/
			if(row[iRow] == NULL)
				break;
			param.id = atoi(row[iRow]);
			iRow++;

			if(row[iRow] == NULL)
				break;
			param.type = row[iRow];
			typeList.insert(num,param);
			iRow++;
			num++;
			result = db_getnext();
		}while(0);
	}

	buymode.InitTypeList(&brandList, &functionList, &typeList);
	stockmode.InitTypeList(&brandList, &functionList, &typeList);
	
}


SongSystem::~SongSystem()
{

}
