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

int Player::DoOperation()
{
	return 0;
}
