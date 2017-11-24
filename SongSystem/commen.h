#ifndef COMMEN_H
#define COMMEN_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <QLabel>
#include <QDateTime>
#include <QDate>

#include "mydb.h"
	
#include <QMessageBox>
	
#include <QTextEdit>
#include <QlineEdit>


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define STOCK_SHOW 	0 
#define	SALE_SHOW	1


#define PERMISSION_NOBODY 	0
#define PERMISSION_USER		1
#define PERMISSION_ROOT		2

typedef struct param
{
	int id;
	QString type;

}tParam;


#endif