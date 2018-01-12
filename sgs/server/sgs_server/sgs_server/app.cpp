#include "app.h"
#include "game.h"

App::App():
	m_stConf_File("./conf/game.conf"),
	m_pLoop(NULL),
	m_pGame(NULL),
	m_nSvrid(0),
	m_bDaemonize(false)
{
}


App::~App()
{
}
