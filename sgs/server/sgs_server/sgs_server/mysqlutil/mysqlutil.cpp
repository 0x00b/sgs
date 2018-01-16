#include "mysqlutil.h"



MySqlUtil::MySqlUtil()
{
}


MySqlUtil::~MySqlUtil()
{
}

int MySqlUtil::ConnMysql(char* ip, char* usr, char* pwd, char* dbname, int port) {
	if (ip == NULL || usr == NULL || pwd == NULL || dbname == NULL)
	{
		return -1;
	}
	mysql_init(&m_con);
	if (mysql_real_connect(&m_con, ip, usr, pwd, dbname, port, NULL, 0))
	{
		mysql_set_character_set(&m_con, "utf8");
		return 0;
	}
	return -1;
}

MYSQL_RES* MySqlUtil::MysqlQuery(char* sql) {
	if (NULL == sql)
	{
		return NULL;
	}
	int res = mysql_query(&m_con, sql);
	if (!res)
	{
		return mysql_store_result(&m_con);
	}
	return NULL;
}

void MySqlUtil::CloseMysql() {
	mysql_close(&m_con);
}