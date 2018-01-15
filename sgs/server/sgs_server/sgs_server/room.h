/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description :
**************************************************/
#ifndef _SGS_ROOM_H_
#define _SGS_ROOM_H_

#include "include.h"
#include "libgamelogic/gamelogic.h"

class Player;

class Room
{
	//variables
private:
	std::list<Player*> m_lstPlayers;	//players in the room
	std::string	m_stName;			//room's name

	GameLogic* m_pGmLgic;
	
	int m_nMaxPlayerCnt;			//max player cnt
	int m_nPlayerCnt;				//current player cnt
	int m_nMatchSeatWay;			//random or by order to give seat number
	int m_nStatus;					//room's status
protected:

public:

	//functions
public:
	Room();
	virtual ~Room();
/*
random cards
dispatch card
start game
*/
	int EnterRoom(Player* player);
	int QuitRoom(Player* player);
	int Broadcast();
	int Unicast(Player* player);
	int Ready(Player* player);
protected:

private:

};
#endif

