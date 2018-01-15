#include "player.h"
#include "app.h"

Player::Player(int fd, std::string stIP):m_iClient(this)
{
	m_iClient.m_nfd = fd;
	m_iClient.m_stIP = stIP;
}


Player::~Player()
{
}

int Player::BeforeDo()
{
	log.info(FFLs);
	return 0;
}

int Player::Do()
{
	log.info(FFLs);

	return 0;
}

int Player::AfterDo()
{
	log.info(FFLs);

	m_iClient.m_iPacket.body.clear();
	m_iClient.m_iPacket.m_nCurLen = 0;
	m_iClient.m_iPacket.m_eStatus = STAT_HEADER;

	return 0;
}
