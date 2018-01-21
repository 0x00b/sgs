#include "game.h"
#include "player.h"
#include "app.h"
#include "ppacket.h"


Game::Game() :m_nStatus(0)
{
	m_mPlayers.clear();
	m_mRooms.clear();
}


Game::~Game()
{
}

int Game::StartUp()
{
	if (Listen() == 0)
	{
		return 0;
	}
	return -1;
}

int Game::UserQuit(Player * player)
{
	m_mPlayers.erase(player->m_iClient.m_nfd);
	delete player;
	return 0;
}

int Game::ReqMatchRoom(Player * player)
{
	return 0;
}

int Game::ReqSelectGameMode(Player * player)
{
	return 0;
}

int Game::ReqGetGameMode(Player * player)
{
	return 0;
}

int Game::ReqCreateRoom(Player * player)
{
	return 0;
}

int Game::ReqEnterRoom(Player * player)
{
	return 0;
}

int Game::ReqEnterRoomFast(Player * player)
{
	return 0;
}

int Game::ReqSearchRoom(Player * player)
{
	return 0;
}

int Game::Broadcast(PPacket* pkt)
{
	std::shared_ptr<PPacket> sptr(pkt);
	for (std::map<int, Player *>::iterator player = m_mPlayers.begin(); player != m_mPlayers.end(); ++player)
	{
		player->second->Send(sptr);
	}
	return 0;
}

int Game::Unicast(Player * player, PPacket* pkt)
{
	std::shared_ptr<PPacket> sptr(pkt);
	player->Send(sptr);
	return 0;
}

const Player * Game::GetOLPlayer(int playerid)
{
	for (std::map<int, Player*>::iterator player = m_mPlayers.begin(); player != m_mPlayers.end(); player++)
	{
		if (playerid == player->second->m_nID)
		{
			return player->second;
		}
	}

	return NULL;
}

int Game::Listen()
{
	sgslog.info(FFL_s_s_d,"Listening on:",
		g_app.m_iConf["app"]["host"].asString().c_str(),
		g_app.m_iConf["app"]["port"].asInt());

	struct sockaddr_in addr;

	m_nListenfd = socket(PF_INET, SOCK_STREAM, 0);
	if (m_nListenfd < 0) {
		sgslog.error(FFL_s, strerror(errno));
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(g_app.m_iConf["app"]["port"].asInt());
	addr.sin_addr.s_addr = inet_addr(g_app.m_iConf["app"]["host"].asString().c_str());
	if (addr.sin_addr.s_addr == INADDR_NONE) {
		sgslog.error(FFL_s,"Incorrect ip address!");
		close(m_nListenfd);
		m_nListenfd = -1;
		return -1;
	}

	int on = 1;
	if (setsockopt(m_nListenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
		sgslog.error(FFL_s_s,"setsockopt failed:", strerror(errno));
		close(m_nListenfd);
		return -1;
	}

	if (bind(m_nListenfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		sgslog.error(FFL_s,"bind failed:", strerror(errno));
		close(m_nListenfd);
		return -1;
	}

	fcntl(m_nListenfd, F_SETFL, fcntl(m_nListenfd, F_GETFL, 0) | O_NONBLOCK);
	listen(m_nListenfd, 1000);

	m_iAccept.data = this;
	ev_io_init(&m_iAccept, Game::Accept_cb, m_nListenfd, EV_READ);
	ev_io_start(g_app.m_pLoop, &m_iAccept);
	sgslog.info(FFL_s,"listen ok");
	return 0;
}

void Game::Accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	if (EV_ERROR & revents) {
		sgslog.error(FFL_s, "got invalid event");
		return;
	}

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	int fd = accept(w->fd, (struct sockaddr *) &client_addr, &client_len);
	if (fd < 0) {
		sgslog.error(FFL_s_s, "accept error:", strerror(errno));
		return;
	}
	Game *game = (Game*)(w->data);

	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);

	Player *player = new (std::nothrow) Player(fd, inet_ntoa(client_addr.sin_addr));
	if (player)
	{
		player->m_iClient.Active();
		game->m_mPlayers[fd] = player;
	}
	else
	{
		close(fd);
	}
	return;
}
