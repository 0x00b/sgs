#include "player.h"
#include "app.h"
#include "room.h"

Player::Player(int fd, std::string stIP):m_iClient(this)
{
	m_iClient.m_nfd = fd;
	m_iClient.m_stIP = stIP;
}


Player::~Player()
{
}

int Player::GetFriends()
{
	return 0;
}

int Player::AddFriends()
{
	return 0;
}

int Player::DeleteFriends()
{
	return 0;
}

int Player::QuitRoom()
{
	return 0;
}

int Player::BeforeDo()
{
	log.info(FFLs);

	if (m_iClient.m_iPacket.check())
	{
		return 0;
	}
	return -1;
}

int Player::Do()
{
	log.info(FFLs);
	return m_pRoom->m_pGmLgic->Do(this);
}

int Player::AfterDo()
{
	log.info(FFLs);

	m_iClient.m_iPacket.body.clear();
	m_iClient.m_iPacket.m_nCurLen = 0;
	m_iClient.m_iPacket.m_eStatus = STAT_HEADER;

	return 0;
}
