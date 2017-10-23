#include "stockmode.h"

StockMode::StockMode(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	connect(btnQuery,SIGNAL(clicked()),this,SLOT(Query()));
	connect(btnClear,SIGNAL(clicked()),this,SLOT(Clear()));

	connect(cbBrand, SIGNAL(clicked()), this, SLOT(BrandCheckChange())); 
	connect(cbFunction, SIGNAL(clicked()), this, SLOT(FunctionCheckChange())); 
	connect(cbType, SIGNAL(clicked()), this, SLOT(TypeCheckChange())); 
	connect(tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(SelectSaleRow())); 
	connect(&salemode, SIGNAL(sigSaleNum(int)), this, SLOT(ProductNumUpdate(int))); 
	
	tableWidget->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//单击选中整行
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  
	dateTimeEdit->setCalendarPopup(true);

	cboxBrand->setEnabled(false);
	cboxFunction->setEnabled(false);
	cboxType->setEnabled(false);
	m_mode = 0;
}

void StockMode::InitTypeList(QList<tParam> *brand,QList<tParam> *func,QList<tParam> *type )
{
	brandList = brand; 
	functionList=func; 
	typeList=type;
	for(int j=0;j<brandList->size();j++)
		cboxBrand->insertItem(j,brandList->at(j).type);
	for(int j=0;j<functionList->size();j++)
		cboxFunction->insertItem(j,functionList->at(j).type);
	for(int j=0;j<typeList->size();j++)
		cboxType->insertItem(j,typeList->at(j).type);

}

void StockMode::setShowMode(int mode)
{
	m_mode = mode;
	Clear();
	for(int i=0;i<tableWidget->columnCount();i++)
	{
		tableWidget->showColumn(i);	
	}
	tableWidget->hideColumn(6);
	if(mode == STOCK_SHOW)
	{

		tableWidget->hideColumn(0);
		tableWidget->hideColumn(10);
		tableWidget->hideColumn(11);
		tableWidget->hideColumn(12);
		tableWidget->hideColumn(13);
		tableWidget->hideColumn(14);
	}
	else if(mode == SALE_SHOW)
	{
		tableWidget->hideColumn(9);
		tableWidget->hideColumn(8);

		
		
	}



}

void StockMode::BrandCheckChange()
{
	if(cbBrand->isChecked())
		cboxBrand->setEnabled(true);
	else
		cboxBrand->setEnabled(false);	

}

void StockMode::FunctionCheckChange()
{
	if(cbFunction->isChecked())
		cboxFunction->setEnabled(true);
	else
		cboxFunction->setEnabled(false);	

}

void StockMode::TypeCheckChange()
{
	if(cbType->isChecked())
		cboxType->setEnabled(true);
	else
		cboxType->setEnabled(false);	

}

void StockMode::Query()
{
	if(m_mode == STOCK_SHOW)
	{
		QueryStock();
	}
	else if(m_mode == SALE_SHOW)
	{
		QuerySale();
	}
}

void StockMode::QuerySale()
{
	void *result;
	char **row;
	int iRow = 0;
	char sql[512]={0};
	int itemRow =0;
	QString bstr;
	QString fstr;
	QString tstr;
	int len=0;
	int checkNum=0;

	len =sprintf(sql,"select id,name,brand,function,type,num,cost_price,sale_price,customer,phone,address,saler,timeval from table_sale_list where id>=0 ");
	for(int i=0;i<tableWidget->rowCount();)
		tableWidget->removeRow(0);
	if(cbBrand->isChecked())
		len +=sprintf(sql+len,"and brand ='%s' ",cboxBrand->currentText().toAscii().data());
	
	if(cbFunction->isChecked())
		len +=sprintf(sql+len,"and function ='%s' ",cboxFunction->currentText().toAscii().data());
	if(cbType->isChecked())
		len +=sprintf(sql+len,"and type ='%s' ",cboxType->currentText().toAscii().data());
		
	if(cbTime->isChecked())
	{
		
		QDateTime datetime =dateTimeEdit->dateTime();
		len +=sprintf(sql+len,"and  timeval>%lu and timeval<%lu+%d ",datetime.toTime_t(),datetime.toTime_t(),3600*24);
	}
	result = db_getfirst(sql);
	while (result)
	{		
		row   = (char **)result;
		iRow  = 0;
		tableWidget->insertRow(itemRow);
		do
		{
			/*id*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,0,new QTableWidgetItem(row[iRow])); 
			iRow++;
			/*name*/
			if(row[iRow] == NULL)
				break;

			tableWidget->setItem(itemRow,1,new QTableWidgetItem(row[iRow])); 
			iRow++;
			/*brand*/
			if(row[iRow] == NULL)
				break;
				tableWidget->setItem(itemRow,2,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*function*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,3,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*type*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,4,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*num*/
			if(row[iRow] == NULL)
				break;

			tableWidget->setItem(itemRow,5,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*cost_price*/
			if(row[iRow] == NULL)
				break;
				tableWidget->setItem(itemRow,6,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*sale_price*/
			if(row[iRow] == NULL)
				break;
				tableWidget->setItem(itemRow,7,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*customer*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,10,new QTableWidgetItem(row[iRow])); 
			iRow++;

				/*phone*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,11,new QTableWidgetItem(row[iRow])); 
			iRow++;
				/*address*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,12,new QTableWidgetItem(row[iRow]));
			iRow++;
				/*saler*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,13,new QTableWidgetItem(row[iRow])); 
			iRow++;
			/*timeval*/
			if(row[iRow] == NULL)
				break;
			QString str = row[iRow];
			QDateTime datetime ;
			datetime=QDateTime::fromTime_t(str.toInt());
			tableWidget->setItem(itemRow,14,new QTableWidgetItem(datetime.toString("yyyy-MM-dd hh:mm:ss"))); 
			iRow++;
			itemRow++;
			result = db_getnext();
		}while(0);
	}
}

void StockMode::QueryStock()
{
	void *result;
	char **row;
	int iRow = 0;
	char sql[512]={0};
	int itemRow =0;
	QString bstr;
	QString fstr;
	QString tstr;
	int len=0;
	int checkNum=0;

	len =sprintf(sql,"select name,brand,function,type,num,cost_price,sale_price,worker,timeval from table_good_list where id>=0 ");
	for(int i=0;i<tableWidget->rowCount();)
		tableWidget->removeRow(0);
	if(cbBrand->isChecked())
		len +=sprintf(sql+len,"and brand ='%s' ",cboxBrand->currentText().toAscii().data());
	
	if(cbFunction->isChecked())
		len +=sprintf(sql+len,"and function ='%s' ",cboxFunction->currentText().toAscii().data());
	if(cbType->isChecked())
		len +=sprintf(sql+len,"and type ='%s' ",cboxType->currentText().toAscii().data());
		
	if(cbTime->isChecked())
	{
		
		QDateTime datetime =dateTimeEdit->dateTime();
		len +=sprintf(sql+len,"and  timeval>%lu and timeval<%lu+%d ",datetime.toTime_t(),datetime.toTime_t(),3600*24);
	}
	
	result = db_getfirst(sql);
	while (result)
	{		
		row   = (char **)result;
		iRow  = 0;
		tableWidget->insertRow(itemRow);
		do
		{
			/*name*/
			if(row[iRow] == NULL)
				break;

			tableWidget->setItem(itemRow,1,new QTableWidgetItem(row[iRow])); 
			iRow++;
			/*brand*/
			if(row[iRow] == NULL)
				break;
				tableWidget->setItem(itemRow,2,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*function*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,3,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*type*/
			if(row[iRow] == NULL)
				break;
			tableWidget->setItem(itemRow,4,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*num*/
			if(row[iRow] == NULL)
				break;

			tableWidget->setItem(itemRow,5,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*cost_price*/
			if(row[iRow] == NULL)
				break;
				tableWidget->setItem(itemRow,6,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*sale_price*/
			if(row[iRow] == NULL)
				break;
				tableWidget->setItem(itemRow,7,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*worker*/
			if(row[iRow] == NULL)
				break;
				tableWidget->setItem(itemRow,8,new QTableWidgetItem(row[iRow])); 
			iRow++;

			/*timeval*/
			if(row[iRow] == NULL)
				break;
			QString str = row[iRow];
			QDateTime datetime ;
			datetime=QDateTime::fromTime_t(str.toInt());
			tableWidget->setItem(itemRow,9,new QTableWidgetItem(datetime.toString("yyyy-MM-dd hh:mm:ss"))); 
			iRow++;
			itemRow++;
			result = db_getnext();
		}while(0);
	}

}


void StockMode::SelectSaleRow()
{
	if(m_mode == SALE_SHOW)
		return ;
	int index = tableWidget->currentRow();

	QDateTime time;  
	QString idstr = tableWidget->item(index,8)->text();
	time = QDateTime::fromString(idstr, "yyyy-MM-dd hh:mm:ss");
	salemode.lbId->setText(QString::number(time.toTime_t()));

	
	salemode.lbName->setText(tableWidget->item(index,0)->text());
	salemode.lbBrand->setText(tableWidget->item(index,1)->text());
	salemode.lbFunction->setText(tableWidget->item(index,2)->text());
	salemode.lbType->setText(tableWidget->item(index,3)->text());
	salemode.m_num = tableWidget->item(index,4)->text().toInt();
	salemode.lbTime->setText(time.currentDateTime().toString( "yyyy-MM-dd hh:mm:ss"));
	salemode.cost_price = tableWidget->item(index,5)->text();
	salemode.show();

}


void StockMode::ProductNumUpdate(int num)
{
	int index = tableWidget->currentRow();
	tableWidget->item(index,4)->setText(QString::number(num));
	

}

void StockMode::Clear()
{

	for(int i=0;i<tableWidget->rowCount();)
		tableWidget->removeRow(0);
	tableWidget->clearContents();

}

StockMode::~StockMode()
{

}
