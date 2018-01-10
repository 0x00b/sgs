#ifndef  _SGS_APP_H_
#define  _SGS_APP_H_

/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description : 
**************************************************/

#include "include.h"

/*************************************************
* Class			: App
* Author		: lijun
* Create Date	: 2018.1.9
* Description	: 程序的一些属性配置等
**************************************************/
class App
{
	/*varibles*/

//private:
public:
	std::string		m_stConf_File;
	bool			m_bDaemonize;
	Json::Value		m_iConf;
	struct ev_loop*	m_iLoop;

protected:

public:

	/*functions*/
public:
	App();
	virtual ~App();

protected:

private:

};


#endif // ! _APP_H_



