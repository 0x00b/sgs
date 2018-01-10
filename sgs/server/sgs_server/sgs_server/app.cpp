#include "app.h"



App::App():
	m_bDaemonize(false),
	m_iLoop(NULL),
	m_stConf_File("/conf/game.conf")
{
}


App::~App()
{
}
