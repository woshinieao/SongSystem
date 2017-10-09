#include "sign.h"

Sign::Sign(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

		connect(btnLogin,SIGNAL(clicked()),this,SLOT(Signshow()));


}



void Sign::Signshow()
{
	user = 


}


Sign::~Sign()
{

}
