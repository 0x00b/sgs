/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description :
**************************************************/
#ifndef _SGS_ROOM_H_
#define _SGS_ROOM_H_

#include "include.h"

class Player;

class Room
{
	//variables
private:
	std::list<Player*> m_iPlayers;	//players in the room
	std::string	m_stName;			//room's name
	int m_nMaxPlayerCnt;			//max player cnt
	int m_nPlayerCnt;				//current player cnt
	int m_nMatchSeatWay;			//random or by order to give seat number
	int m_nStatus;					//room's status
protected:

public:

	//functions
public:
	Room();
	~Room();
/*
random cards
dispatch card
start game
*/
	int EnterRoom();
	int QuitRoom();
	int Broadcast();
	int Unicast();

protected:

private:

};
#endif

