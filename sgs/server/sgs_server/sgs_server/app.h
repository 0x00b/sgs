/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description : 
**************************************************/

#ifndef  _SGS_APP_H_
#define  _SGS_APP_H_

#include "log.h"

class Game;

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
	SGSLog			m_iLog;
	std::string		m_stConf_File;
	Json::Value		m_iConf;
	struct ev_loop*	m_pLoop;
	Game*			m_pGame;
	int				m_nSvrid;
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

extern App g_app;

#endif // ! _APP_H_



