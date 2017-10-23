#ifndef _MY_DB_INCLUDE_H
#define _MY_DB_INCLUDE_H

////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)


#define SQL_TYPE_NORMAL             0     /*一般SQL语句*/
#define SQL_TYPE_INSERT_TEMP        1     /*插入温度记录*/    
#define SQL_TYPE_UPDATE_LAST_TEMP   2     /*更新最近温度记录*/
#define SQL_TYPE_INSERT_FILE_LOG    3     /*插入文件记录*/
#define SQL_TYPE_ALARM              4     /*告警*/


enum db_result {
    DB_FAILURE=-1, DB_SUCCESS=0
};

typedef struct {
    char host[32];
    char username[32];
    char password[32];
    char database[32];
} MySQLConf;


typedef struct db_ops {
    char db_sys[15]; // name of the database system.

    void   *conn;
    MySQLConf *db_conf;
    /*
     * Open db connection with given config params.
     * Config params are specificaly for each database type.
     * return NULL if error occurs ; established connection's pointer otherwise
     */
    void *(*open) (MySQLConf *conf);
    /*
     * close given connection.
     */
    void (*close) ();
    /*
     * check if given connection still alive,
     * return -1 if not or error occurs ; 0 if all was fine
     * NOTE: this function is optional
     */
    int (*check) ();
    /*
     * Destroy specificaly configuration struct.
     */
    void (*conf_destroy) (MySQLConf *conf);
    /*
    * excute sql string.
    */
    int (*excute) (const char *sqlstr);
    /*
    * get first row of the table, return columns.
    */
    void *(*getfirst) (const char *sqlstr);
    /*
    * get next row of the table, return columns.
    */
    void *(*getnext) ();
    /*
    * flush table.
    */
    int (*flush) (const char *table);

	int (*geterrno) ();
} db_ops;

#pragma pack()


db_ops *db_init_mysql();

int  db_check();
int  db_excute(const char *sql);
void *db_getfirst(const char *sql);
void *db_getnext();
int   db_flush(const char *table);

db_ops *  db_init();
void db_shutdown();
int  db_restart();

int  db_errno();

void PushSQL(char *sql,char type);


#endif

