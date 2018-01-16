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
	std::list<Player*> m_lstPlayers;//players in the room
	std::string	m_stName;			//room's name

	int m_nType;					//room type
	int m_nMaxPlayerCnt;			//max player cnt
	int m_nPlayerCnt;				//current player cnt
	int m_nMatchSeatWay;			//random or by order to give seat number
	int m_nStatus;					//room's status
protected:

public:
	GameLogic* m_pGmLgic;

	//functions
public:
	Room();
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

/*


The InnoDB cluster 'sandboxCluster' is available on the following ports:

localhost:3310 through localhost:3330

To connect with the MySQL Shell execute the following command:

mysqlsh root@localhost:3310

To bootstrap the MySQL Router execute the following command:

mysqlrouter --bootstrap root@localhost:3310 --directory router-sandbox

*/
#endif

