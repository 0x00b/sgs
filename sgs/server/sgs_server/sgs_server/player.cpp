#include "player.h"



Player::Player(int fd)
{
	m_iClient.m_nfd = fd;
}


Player::~Player()
{
}

int Player::DoOperation()
{
	return 0;
}
