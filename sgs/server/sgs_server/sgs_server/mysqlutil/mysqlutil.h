#ifndef _SGS_MYSQLUTIL_H_
#define _SGS_MYSQLUTIL_H_

/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.16
Description :
**************************************************/

#include "../include.h"

class MySqlUtil
{
public:
	MYSQL m_con;

public:
	MySqlUtil();
	~MySqlUtil();
	static int ConnMysql(char* ip, char* usr, char* pwd, char* dbname, int port);
	static MYSQL_RES* MysqlQuery(char* sql);
	static void CloseMysql();

};

#endif
