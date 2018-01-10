#include "app.h"

App::App():
	m_stConf_File("./conf/game.conf"),
	m_iLoop(NULL),
	m_iGame(NULL),
	m_bDaemonize(false)
{
}


App::~App()
{
}
