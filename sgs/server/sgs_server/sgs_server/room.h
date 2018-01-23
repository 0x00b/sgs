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

enum ERoomType
{
	ROOM_TYPE_3 = 3,
	ROOM_TYPE_6 = 6,
	ROOM_TYPE_8 = 8,
};

class Room
{
	//variables
private:
	std::list<Player*> m_lstPlayers;//players in the room
	std::string	m_stName;			//room's name

	ERoomType m_eType;				//room type

	int m_nRoomID;
	int m_nMaxPlayerCnt;			//max player cnt
	int m_nPlayerCnt;				//current player cnt
	int m_nMatchSeatWay;			//random or by order to give seat number
	int m_nStatus;					//room's status
protected:

public:
	GameLogic* m_pGmLgic;

	//functions
public:
	Room(GameLogic* plogic);
	virtual ~Room();

	int EnterRoom(Player* player);
	int QuitRoom(Player* player);
	int Broadcast();
	int Unicast(Player* player);
	int Ready(Player* player);

	virtual int Do(Player* player);
protected:

private:

};


#endif

