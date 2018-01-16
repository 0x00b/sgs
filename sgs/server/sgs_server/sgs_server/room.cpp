#include "room.h"



Room::Room()
{
}


Room::~Room()
{
}

int Room::EnterRoom(Player * player)
{
	return 0;
}

int Room::QuitRoom(Player * player)
{
	return 0;
}

int Room::Broadcast()
{
	return 0;
}

int Room::Unicast(Player * player)
{
	return 0;
}

int Room::Ready(Player * player)
{
	return 0;
}

int Room::Do(Player* player)
{
	if (NULL != m_pGmLgic)
	{
		return m_pGmLgic->Do(player);
	}
	return -1;
}
