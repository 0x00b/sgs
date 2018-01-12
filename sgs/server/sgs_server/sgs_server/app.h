/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description : 
**************************************************/

#ifndef  _SGS_APP_H_
#define  _SGS_APP_H_

#include "log.h"
#include "game.h"

/*************************************************
* Class			: App
* Author		: lijun
* Create Date	: 2018.1.9
* Description	: 
**************************************************/
class App
{
	/*varibles*/

//private:
public:
	std::string		m_stConf_File;
	Json::Value		m_iConf;
	SGSLog			m_iLog;
	struct ev_loop*	m_iLoop;
	Game*			m_iGame;
	bool			m_bDaemonize;
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



