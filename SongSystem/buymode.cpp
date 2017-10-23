#include "buymode.h"

BuyMode::BuyMode(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	connect(btnAddtype,SIGNAL(clicked()),this,SLOT(AddType()));
	connect(btnDelType,SIGNAL(clicked()),this,SLOT(DelType()));
	connect(cboxType,SIGNAL(currentIndexChanged(int)),this,SLOT(TypeChangeShow(int)));
	connect(btnInbound,SIGNAL(clicked()),this,SLOT(Inbound()));
	connect(btnInboundCancel,SIGNAL(clicked()),this,SLOT(InboundCancel()));

	QRegExp ipRegExp1 = QRegExp("^[1-9][0-9][0-9][0-9][0-9]");
	QRegExp ipRegExp = QRegExp("\\d+\\.\\d{2}");
	
	for(int i=0;i<tableWidget->rowCount();i++)
	{
		QTableWidgetItem *item1 = new QTableWidgetItem();
		tableWidget->setItem(i,0,item1);
		QLineEdit *item2 = new QLineEdit("1");
		QRegExpValidator *ipRegExpValidator1 = new QRegExpValidator(ipRegExp1, this);
		item2->setValidator(ipRegExpValidator1);
		tableWidget->setCellWidget(i,4,item2);


		QRegExpValidator *ipRegExpValidator2 = new QRegExpValidator(ipRegExp, this);
		QLineEdit *item3 = new QLineEdit("0.00");
		item3->setValidator(ipRegExpValidator2);
		tableWidget->setCellWidget(i,5,item3);
		QLineEdit *item4 = new QLineEdit("0.00");
		item4->setValidator(ipRegExpValidator2);
		tableWidget->setCellWidget(i,6,item4);
	
	}
}

void BuyMode::InitTypeList(QList<tParam> *brand,QList<tParam> *func,QList<tParam> *type )
{
	brandList = brand; 
	functionList=func; 
	typeList=type;
	for(int i=0;i<10;i++)
	{
		tableWidget->setCellWidget(i, 1, (QWidget*)&comboxbrandList[i]);
		for(int j=0;j<brandList->size();j++)
			comboxbrandList[i].insertItem(j,brandList->at(j).type);

		tableWidget->setCellWidget(i, 2, (QWidget*)&comboxfunctionList[i]);
		for(int j=0;j<functionList->size();j++)
				comboxfunctionList[i].insertItem(j,functionList->at(j).type);
		
		tableWidget->setCellWidget(i, 3, (QWidget*)&comboxtypeList[i]);
		for(int j=0;j<typeList->size();j++)
				comboxtypeList[i].insertItem(j,typeList->at(j).type);
	}
	cboxType->setCurrentIndex(0);
	TypeChangeShow(0);
}


void BuyMode::TypeChangeShow(int index)
{

	QList<tParam> *p = NULL ;
	switch(index)
	{
	case 0:
		p = brandList;
		break;
	case 1:
		p = functionList;
		break;
	case 2:
		p = typeList;
		break;

	default :
		return ;
	}
	int num = cboxTypeList->count(); 
	for(int i=0;i<num;i++ )
		cboxTypeList->removeItem(0);
	for(int j=0;j<p->size();j++)
		cboxTypeList->insertItem(j,p->at(j).type);
	
}


void BuyMode::AddType()
{
	QList<tParam> *p = NULL ;
	QComboBox *pbox=NULL;
	tParam param;
	char sql[256]={0};
	int index = cboxType->currentIndex();
	param.type = leType->text();
	switch(index)
	{
	case 0:
		p = brandList;
		pbox = comboxbrandList;
		param.id = p->at(p->size()-1).id +1;
		sprintf(sql,"insert into table_brand_list(id,brand_name) value(%d,'%s') ",param.id,param.type.toAscii().data());
		break;
	case 1:
		p = functionList;
		pbox = comboxfunctionList;
		param.id = p->at(p->size()-1).id +1;
		sprintf(sql,"insert into table_function_list(id,function_name) value(%d,'%s') ",param.id,param.type.toAscii().data());
		break;
	case 2:
		p = typeList;
		pbox = comboxtypeList;
		param.id = p->at(p->size()-1).id +1;
		sprintf(sql,"insert into table_type_list(id,type_name) value(%d,'%s') ",param.id,param.type.toAscii().data());
		break;
	}
	p->insert(p->size(),param);
	for(int i=0;i<10;i++)
		pbox[i].insertItem(pbox[i].count(),param.type);
	cboxTypeList->insertItem(cboxTypeList->count(),param.type);
	db_excute(sql);
	leType->clear();
}


void BuyMode::DelType()
{
	QList<tParam> *p = NULL ;
	QComboBox *pbox=NULL;
	tParam param;
	char sql[256]={0};
	int index = cboxType->currentIndex();
	int indexItem = cboxTypeList->currentIndex();


	switch(index)
	{
	case 0:
		p = brandList;
		pbox = comboxbrandList;
		param = p->at(indexItem);
		sprintf(sql,"delete from table_brand_list where id=%d and brand_name='%s' ",param.id,param.type.toAscii().data());
		break;
	case 1:
		p = functionList;
		pbox = comboxfunctionList;
		param = p->at(indexItem);
		sprintf(sql,"delete from table_function_list where id=%d and function_name='%s' ",param.id,param.type.toAscii().data());
		break;
	case 2:
		p = typeList;
		pbox = comboxtypeList;
		param = p->at(indexItem);
		sprintf(sql,"delete from table_type_list where id=%d and type_name='%s'",param.id,param.type.toAscii().data());
		break;
	}
	p->removeAt(indexItem);
	cboxTypeList->removeItem(indexItem);
	for(int i=0;i<10;i++)
		pbox[i].removeItem(indexItem);
	db_excute(sql);
}



void BuyMode::Inbound()
{
	char sql[512]={0};
	QWidget * widget;
	QComboBox *combox;
	QLineEdit *le;
	time_t now = time(NULL);
	QString person = lePerson->text();
	if(person.isEmpty())
	{
		QMessageBox box(QMessageBox::Warning,"错误","入库人员名称未填写！！");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.exec();
		return;
	
	}

	/*
	for(int i=0;i<tableWidget->rowCount();i++)
	{
		if(tableWidget->item(i,0)->text().isEmpty())
		{
			QMessageBox box(QMessageBox::Warning,"错误","有商品名称为空 ！！");
			box.setStandardButtons (QMessageBox::Ok);
			box.setButtonText (QMessageBox::Ok,QString("确 定"));
			box.exec();
			return;
		}
	}
	*/
	for(int i=0;i<tableWidget->rowCount();i++)
	{
		QString namestr = tableWidget->item(i,0)->text();
		if(namestr.isEmpty())
			continue;

			widget=tableWidget->cellWidget(i,1);//获得widget
			combox=(QComboBox*)widget;//强制转化为QComboBox
			QString brandstr=combox->currentText(); 

			widget=tableWidget->cellWidget(i,2);//获得widget
			combox=(QComboBox*)widget;//强制转化为QComboBox
			QString functionstr=combox->currentText(); 

			widget=tableWidget->cellWidget(i,3);//获得widget
			combox=(QComboBox*)widget;//强制转化为QComboBox
			QString typestr=combox->currentText(); 



			widget=tableWidget->cellWidget(i,4);//获得widget
			le=(QLineEdit*)widget;//强制转化为QComboBox
			int typenum=le->text().toInt(); 

			widget=tableWidget->cellWidget(i,5);//获得widget
			le=(QLineEdit*)widget;//强制转化为QComboBox
			float cost_price=le->text().toFloat();

			widget=tableWidget->cellWidget(i,6);//获得widget
			le=(QLineEdit*)widget;//强制转化为QComboBox
			float sale_price=le->text().toFloat(); 

			sprintf(sql,"insert into table_good_list(name,brand,function,type,worker,num,cost_price,sale_price,timeval) values ('%s','%s','%s','%s','%s',%d,%.2f,%.2f,%lu);",
				namestr.toAscii().data(),brandstr.toAscii().data(),functionstr.toAscii().data(),typestr.toAscii().data(),person.toAscii().data(),
				typenum,cost_price,sale_price,now);
			db_excute(sql);
		
	}


}

void BuyMode::InboundCancel()
{



}

BuyMode::~BuyMode()
{

}
