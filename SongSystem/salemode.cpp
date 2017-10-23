#include "salemode.h"

#include "salemode.h"

SaleMode::SaleMode(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	connect(btnSale, SIGNAL(clicked()), this, SLOT(Sale())); 
	connect(btnPrint, SIGNAL(clicked()), this, SLOT(Print())); 
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(Cancel())); 
}


void SaleMode::Sale()
{

	char sql[1024]={0};


	int id = lbId->text().toInt();
	QString name = lbName->text();
	QString brand = lbBrand->text();
	QString func = lbFunction->text();
	QString type = lbType->text();
	QString customer = leCustomer->text();
	
	QString phone = lePhone->text();
	int num = leNum->text().toInt();
	QString price = leSaleprice->text();
	QString saler = leSaler->text();

	if(id<0 || price.isEmpty()||num<=0)
	{
		QMessageBox box(QMessageBox::Warning,"提示","销售价格和数量不能为空！");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.exec();
		return;
	
	}
	if(num>m_num)
	{
		QMessageBox box(QMessageBox::Warning,"提示","库存数量不足！");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.exec();
		return;
	
	}
	 
	QString idstr = lbTime->text();
	QDateTime timedate = QDateTime::fromString(idstr, "yyyy-MM-dd hh:mm:ss");
	long timeval =timedate.toTime_t();
	QString address = teAddress->toPlainText();
	sprintf(sql,"insert into table_sale_list(id,name,brand,function,type,num,customer,cost_price,sale_price,phone,address,saler,timeval) values(%d,'%s','%s','%s','%s',%d,'%s',%.2f,%.2f,'%s','%s','%s',%ld) ",
		id,name.toAscii().data(),brand.toAscii().data(),func.toAscii().data(),type.toAscii().data(),num,customer.toAscii().data(),cost_price.toFloat(),price.toFloat(),phone.toAscii().data(),address.toAscii().data(),saler.toAscii().data(),timeval);
	if(db_excute(sql)== DB_FAILURE)
	{
		QMessageBox box(QMessageBox::Warning,"提示","出单失败！");
		box.setStandardButtons (QMessageBox::Ok);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.exec();
		
	}
	else
	{
		char sqlup[512];
		sprintf(sqlup,"update table_good_list set num = %d where name='%s' and brand='%s' and function='%s' and type='%s'",m_num-num,name.toAscii().data(),brand.toAscii().data(),func.toAscii().data(),type.toAscii().data());
		db_excute(sqlup);
		emit sigSaleNum(m_num-num);
		/*
		QMessageBox box(QMessageBox::Warning,"提示","是否打印销售单据？");
		box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText (QMessageBox::Ok,QString("确 定"));
		box.setButtonText (QMessageBox::Cancel,QString("取 消"));
		if(box.exec()==QDialog::Accepted)
		{
			emit sigSaleBill();
		}
		
		else
		{
			clearInfo();
			close();
		}
		*/
		clearInfo();
		close();
	
	}

}


void SaleMode::Print()
{

}

void SaleMode::Cancel()
{

}

void SaleMode::clearInfo()
{
	lbId->clear();
	lbName->clear();
	lbBrand->clear();
	lbFunction->clear();
	lbType->clear();
	leCustomer->clear();
	lePhone->clear();
	leNum->clear();
	leSaleprice->clear();
	leSaler->clear();
	lbTime->clear();
	teAddress->clear();
}

SaleMode::~SaleMode()
{

}
