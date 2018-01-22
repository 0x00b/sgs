#include "mysqlutil.h"

MYSQL MySqlUtil::m_con;

MySqlUtil::MySqlUtil()
{
}


MySqlUtil::~MySqlUtil()
{
}

int MySqlUtil::ConnMysql(const char* ip, const char* usr, const char* pwd, const char* dbname, int port)
{
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

int MySqlUtil::MysqlQuery(MYSQL_RES*& res, const char* sql) {
	if (NULL == sql)
	{
		return 0;
	}
	int nRet = mysql_query(&m_con, sql);
	if (!nRet)
	{
		res = mysql_store_result(&m_con);
		return mysql_affected_rows(&m_con);
	}
	return 0;
}

void MySqlUtil::CloseMysql() {
	mysql_close(&m_con);
}