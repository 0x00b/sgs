#include "client.h"
#include "app.h"
#include "player.h"


Client::Client(Player* p):m_pPlayer(p)
{
}


Client::~Client()
{
	ev_io_stop(g_app.m_pLoop, &m_ev_read);
	ev_io_stop(g_app.m_pLoop, &m_ev_write);
	close(m_nfd);
}

int Client::Active()
{
	m_ev_read.data = this;

	ev_io_init(&m_ev_read, Client::Read_cb, m_nfd, EV_READ);
	ev_io_start(g_app.m_pLoop, &m_ev_read);

	ev_io_init(&m_ev_write, Client::Write_cb, m_nfd, EV_WRITE);
	return 0;
}

void Client::Read_cb(struct ev_loop * loop, ev_io * w, int revents)
{
	return;
}

void Client::Write_cb(struct ev_loop * loop, ev_io * w, int revents)
{
	return;
}
