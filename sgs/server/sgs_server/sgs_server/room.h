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
#include "protoco/appproto.pb.h"

class Player;
class PPacket;

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
protected:

public:
	GameLogic* m_pGmLgic;
	Player* m_pMaster;	//room master

	std::list<Player*> m_lstPlayers;//players in the room
	std::string	m_stName;			//room's name
	ERoomType m_eType;				//room type

	int m_nRoomID;
	int m_nMaxPlayerCnt;			//max player cnt
	int m_nPlayerCnt;				//current player cnt
	int m_nMatchSeatWay;			//random or by order to give seat number
	int m_nStatus;					//room's status

	//functions
public:
	Room(GameLogic* plogic, int roomid,ERoomType type, const std::string& name);
	virtual ~Room();

	int EnterRoom(Player* player);
	int QuitRoom(Player* player);
	int Broadcast(PPacket* pkt);
	int Unicast(Player* player, PPacket* pkt);
	int Ready(Player* player);

	int CheckGameStart();

	virtual int Do(Player* player);
	

	void Get(proto::game::Room* proom);
	void Set(const proto::game::Room& proom);
protected:

private:

};


#endif

