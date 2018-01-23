#include "room.h"



Room::Room(GameLogic* plogic):
	m_pGmLgic(plogic)
{

}


Room::~Room()
{
	delete m_pGmLgic;
}

int Room::EnterRoom(Player *player)
{
	if (NULL != player)
	{
		if (m_nPlayerCnt < m_nMaxPlayerCnt)
		{
			m_lstPlayers.push_back(player);
			m_nPlayerCnt++;
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return -1;
}

int Room::QuitRoom(Player * player)
{
	if(NULL != player)
	{
		//for()
		m_nPlayerCnt++;
		return 0;
	}
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
