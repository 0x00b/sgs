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
	static MYSQL m_con;

public:
	MySqlUtil();
	~MySqlUtil();
	static int ConnMysql(const char* ip,const char* usr,const char* pwd,const char* dbname, int port);
	static MYSQL_RES* MysqlQuery(const char* sql);
	static void CloseMysql();

};

#endif
