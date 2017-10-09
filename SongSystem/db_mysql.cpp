#include "gaurd.h"

#include "StdAfx.h"
#include <winsock2.h>
#include "mysql.h"

#include "debug.h"
#include "mydb.h"
#include "inifile.h"



static MYSQL       *mysql_conn  = NULL;
static MYSQL_RES   *mysql_res   = NULL;
//static MYSQL_FIELD *mysql_field = NULL;
static MYSQL_ROW   *mysql_row   = NULL;
char log_file[256];


////////////////////////////////////////////////////////////////////////////////
static void *mysql_open_conn(MySQLConf *conf )
{
	char value = 1;
	
    /* sanity check */
    if (conf == NULL)
        return NULL;

    /* pre-allocate */
    mysql_conn = (MYSQL*)malloc(sizeof(MYSQL));
    if (mysql_conn == NULL)
        return NULL;

    /* initialize mysql structures */
    if (!mysql_init(mysql_conn))
    {
        OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL, "MYSQL: init failed! %s\n", mysql_error(mysql_conn));
        goto failed;
    }

    if (!mysql_real_connect(mysql_conn, conf->host, conf->username, conf->password,
        conf->database, 0, NULL, 0))
    {
        OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL, "MYSQL: can not connect to database! %s\n", mysql_error(mysql_conn));
        goto failed;
    }
	
	mysql_query(mysql_conn, "SET NAMES GB2312 ");

//	mysql_options(mysql_conn, MYSQL_OPT_RECONNECT, (char *)&value);

    OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL,"MYSQL: Succeeded connected to server at %s.\n", conf->host);
    OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL,"MYSQL: server version %s, client version %s.\n",
           mysql_get_server_info(mysql_conn), mysql_get_client_info());

    return mysql_conn;

failed:
    if (mysql_conn != NULL)
        free(mysql_conn);
    return NULL;
}

static void mysql_close_conn()
{
    OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL,"mysql db close connection......\n");

    if (mysql_conn == NULL)
        return;

    mysql_close((MYSQL*) mysql_conn);
    free(mysql_conn);
    mysql_conn = NULL;
}

static int mysql_check_conn()
{
    if (mysql_conn == NULL)
        return DB_FAILURE;
    if (mysql_ping((MYSQL*)mysql_conn))
    {
        OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL, "MYSQL: database check failed! %s\n", mysql_error(mysql_conn));
        return DB_FAILURE;
    }
    return DB_SUCCESS;
}

static void mysql_conf_destroy(MySQLConf *db_conf)
{
	OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL, "mysql db destroy......\n");
    if (db_conf == NULL)
        return;
    free(db_conf);
}

static int mysql_db_excute(const char *sqlstr)
{
    if (!mysql_query((MYSQL *)mysql_conn, sqlstr))
        return DB_SUCCESS;
    return DB_FAILURE;
}

static void* mysql_db_firstrow(const char *sqlstr)
{
    if (sqlstr == NULL)
        return NULL;

    if (mysql_db_excute(sqlstr) == DB_FAILURE)
        return NULL;

    // we must check this.
    if (mysql_res)
        mysql_free_result(mysql_res);

    mysql_res = mysql_store_result(mysql_conn);
    if (mysql_res == NULL)
        return NULL;
    if (mysql_num_rows(mysql_res) < 1)
    {
        OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL, "Could not get count of table. sql: %s\n", sqlstr);
        mysql_free_result(mysql_res);
        mysql_res = NULL;
        return NULL;
    }
    mysql_row = (MYSQL_ROW *)mysql_fetch_row(mysql_res);
    if (mysql_row == NULL)
    {
        OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL, "rows found but could not load them. sql: %s\n", sqlstr);
        mysql_free_result(mysql_res);
        mysql_res = NULL;
        return NULL;
    }

    return (void *)mysql_row;
}

static void* mysql_db_nextrow()
{
    if (mysql_res == NULL)
        return NULL;
    mysql_row = (MYSQL_ROW *)mysql_fetch_row(mysql_res);
    if (mysql_row == NULL)
    {
        //WriteLog(LOG_SYS_ERR, "\ndb.mysql, rows found but could not load them");
        mysql_free_result(mysql_res);
        mysql_res = NULL;
        return NULL;
    }
    if (mysql_row == NULL)
    {
        mysql_free_result(mysql_res);
        mysql_res = NULL;
        return NULL;
    }

    return (void *)mysql_row;
}

static int mysql_db_flush(const char *table)
{
    char sqlstr[128];
    if (table == NULL)
        return DB_FAILURE;    
    sprintf(sqlstr, "truncate %s;", table);
    //sprintf(sqlstr, "DELETE FROM %s;", table);

    return mysql_db_excute(sqlstr);
}

static int mysql_db_errno()
{
  if (mysql_conn == NULL)
      return DB_FAILURE;
  int err = mysql_errno(mysql_conn);
  if(err == 1043 || err == 1081 || err == 1129)
  	return DB_FAILURE;
  
  return DB_SUCCESS;
}


char* GetWorkingPath()
{
    int iResult = 0;
    static char pPath[_MAX_PATH];
    static BOOL bInit = FALSE;
    if(bInit)
        return pPath;
   
    iResult = GetModuleFileName(NULL,pPath,_MAX_PATH);
    if(iResult == 0 || iResult>= _MAX_PATH)
        return NULL;
    while(pPath[iResult] != '\\' && iResult>= 0)
    {
        iResult--;
    }
    pPath[iResult] = 0; 
    bInit = TRUE;
    return pPath;
}

////////////////////////////////////////////////////////////////////////////////
static struct db_ops mysql_ops;

////////////////////////////////////////////////////////////////////////////////



db_ops *db_init_mysql()
{
    MySQLConf *db_conf = NULL;
    char      filename[128];
	char      buf[64];
	
    OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL,"db init mysql......\n");

    mysql_ops.open         = mysql_open_conn;
    mysql_ops.close        = mysql_close_conn;
    mysql_ops.check        = mysql_check_conn;
    mysql_ops.conf_destroy = mysql_conf_destroy;
    mysql_ops.excute       = mysql_db_excute;
    mysql_ops.getfirst     = mysql_db_firstrow;
    mysql_ops.getnext      = mysql_db_nextrow;
    mysql_ops.flush        = mysql_db_flush;
	mysql_ops.geterrno     = mysql_db_errno;

    sprintf(filename, "%s/%s", GetWorkingPath(), SYS_CFG);
	
	db_conf = (MySQLConf *)malloc(sizeof(MySQLConf));
    if (db_conf == NULL)
    {
        return NULL;
    }
	
	if( CFG_get_key(filename, "LOG", "LOG", buf ) == CFG_OK)
		sprintf(log_file,"D:\\var\\www\\media\\log\\gaurd.log",buf);
	else
		strcpy(log_file,"D:\\var\\www\\media\\log\\gaurd.log");	
	printf("%s\n",log_file);

	if( CFG_get_key(filename, "DB", "HOST", buf ) == CFG_OK)
		strncpy(db_conf->host,buf,32);
	else
		strcpy(db_conf->host,"localhost");
	printf("HOST:%s\n",db_conf->host);

	if( CFG_get_key(filename, "DB", "DATABASE", buf ) == CFG_OK)
		strncpy(db_conf->database,buf,32);
	else
		strcpy(db_conf->database,"db_gp");

	if( CFG_get_key(filename, "DB", "USER", buf ) == CFG_OK)
		strncpy(db_conf->username,buf,32);
	else
		strcpy(db_conf->username,"admin");

	if( CFG_get_key(filename, "DB", "PASSWORD", buf ) == CFG_OK)
		strncpy(db_conf->password,buf,32);
	else
		strcpy(db_conf->password,"admin");	


    sprintf(mysql_ops.db_sys, "mysql");
    mysql_ops.db_conf = db_conf;
    mysql_ops.conn    = (void *)mysql_ops.open(db_conf);
    if (!mysql_ops.conn)
    {
        OSA_DEBUG(DEBUG_PRINT,DEBUG_MODULE_MYSQL,"[db_init_mysql] connect db failure!\n");
        return NULL;
    }

    return &mysql_ops;
}


