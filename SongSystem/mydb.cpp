


#include <windows.h>

#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <io.h>
#include <direct.h>
//#include <TlHelp32.h>
#include "mysql.h"
#include "mydb.h"


 int db_connected;

static db_ops *gndb_ops = NULL;
static db_ops *db_ptr = NULL;

#define MAX_SQL_NUM  256

static unsigned long sql_head = 0;
static unsigned long sql_tail = 0;
static char str_sql[MAX_SQL_NUM][512];
static char sql_type[MAX_SQL_NUM];

HANDLE sql_mutex;
HANDLE db_excute_mutex;

void PushSQL(char *sql,char type)
{
	int tail = 0;
	if(strlen(sql) >= 512)
		return;
	WaitForSingleObject(sql_mutex,INFINITE);
	tail = (sql_tail%MAX_SQL_NUM);
	strcpy(str_sql[tail],sql);
	sql_type[tail] = type;
	sql_tail++;
	ReleaseMutex(sql_mutex);
}


void DbExecuteThread(void *arg)
{
	char *sql = NULL;
	//char type = SQL_TYPE_NORMAL;
	int head = 0;
	while(1)
	{
		WaitForSingleObject(sql_mutex,INFINITE);
		if(sql_tail <= sql_head)
		{		
			ReleaseMutex(sql_mutex);
			Sleep(100);
			continue;
		}
		head = sql_head%MAX_SQL_NUM;
		
		sql  = str_sql[head];
	//	type = sql_type[head];
		
		sql_head++;
		
		if(sql[0] != '\0')
		{
			int ret = 0;
			ret = db_excute(sql);
			if(ret == DB_FAILURE )
			{
				printf("sql Excute:%s\n",sql);
				if (db_errno() != DB_SUCCESS)
			 		db_connected = DB_FAILURE;
			}
			//printf("sql Excute:%s\n",sql);
		}
		sql[0] = '\0';
		
		ReleaseMutex(sql_mutex);
		
		if(db_connected != DB_SUCCESS)
			Sleep(5000);
	}
	
	_endthread();	
}

int db_check()
{
	int ret = DB_FAILURE;
	if(gndb_ops == NULL)
		return DB_FAILURE;

	WaitForSingleObject(db_excute_mutex,INFINITE);
	ret = gndb_ops->check();
	ReleaseMutex(db_excute_mutex);
	
    return ret;
}

int  db_errno()
{
	int ret = DB_FAILURE;
	if(gndb_ops == NULL)
		return DB_FAILURE;

	WaitForSingleObject(db_excute_mutex,INFINITE);	
	ret = gndb_ops->geterrno();
	ReleaseMutex(db_excute_mutex);
	
    return ret;
}

int db_excute(const char *sql)
{
	int ret = DB_FAILURE;
	if(gndb_ops == NULL)
		return DB_FAILURE;
	
	WaitForSingleObject(db_excute_mutex,INFINITE);
	ret = gndb_ops->excute(sql);
	ReleaseMutex(db_excute_mutex);
	
    return ret;
}

void *db_getfirst(const char *sql)
{
	void* result = NULL;
	if(gndb_ops == NULL)
		return result;

	WaitForSingleObject(db_excute_mutex,INFINITE);	
	result = gndb_ops->getfirst(sql);
	ReleaseMutex(db_excute_mutex);
	
    return result;
}

void *db_getnext()
{
	void* result = NULL;
	if(gndb_ops == NULL)
		return result;

	WaitForSingleObject(db_excute_mutex,INFINITE);
	result = gndb_ops->getnext();
	ReleaseMutex(db_excute_mutex);

    return result;
}

int db_flush(const char *table)
{
	int ret = DB_FAILURE;
	if(gndb_ops == NULL)
		return DB_FAILURE;
	
	WaitForSingleObject(db_excute_mutex,INFINITE);	
	ret = gndb_ops->flush(table);
	ReleaseMutex(db_excute_mutex);
	
    return ret;
}

db_ops * db_init()
{

    db_ptr = db_init_mysql();

    if (!db_ptr)
    {
        return db_ptr;
    }
    gndb_ops = db_ptr;

	sql_mutex       = CreateMutex(NULL, FALSE,NULL);
	db_excute_mutex = CreateMutex(NULL, FALSE,NULL);

	memset(str_sql,0,sizeof(str_sql));
	memset(sql_type,0,sizeof(sql_type));

	_beginthread(DbExecuteThread,0,NULL);

    return gndb_ops;
}

int  db_geterrno()
{
	if (!db_ptr)
    {
        return DB_FAILURE;
    }
	return gndb_ops->geterrno();
}

void db_shutdown()
{
    if (!db_ptr)
        return;

    db_ptr->close();
    db_ptr->conf_destroy(db_ptr->db_conf);

    gndb_ops = NULL;
    db_ptr   = NULL;
}

int db_restart()
{
    db_ops *ptr;
    db_ptr = db_init_mysql();

    if (!db_ptr)
    {
        return DB_FAILURE;
    }
    ptr      = gndb_ops;
    gndb_ops = db_ptr;

    // close the old one.
    if (ptr)
    {
        //ptr->close(ptr->conn);
        ptr->conf_destroy(ptr->db_conf);
    }


    return DB_SUCCESS;
}

