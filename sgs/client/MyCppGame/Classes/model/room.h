/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description :
**************************************************/
#ifndef _SGS_ROOM_H_
#define _SGS_ROOM_H_

#include "jsonproto/jsonproto.h"
#include "./libs/json/json.h"
#include <list>
#include "hero.h"
#include "player.h"

class PPacket;

enum ERoomType
{
	ROOM_TYPE_2 = 2,
	ROOM_TYPE_6 = 6,
	ROOM_TYPE_8 = 8,
};

enum EMatchSeatWay
{
	MATCH_SEAT_ORDER = 1,
	MATCH_SEAT_RAND = 2
};

class Room
{
	//variables
private:
protected:

public:

	std::string m_stMaster;	//room master
	std::string m_stNewPlayer;

	std::list<Player> m_lstPlayers;//players in the room
	std::list<std::string> m_chat_message;  //chat message
	std::string	m_stName;			//room's name
	ERoomType m_eType;				//room type
	std::vector<Hero> hero_all_detail;
	int m_nRoomID;
	int m_nMaxPlayerCnt;			//max player cnt
	int m_nPlayerCnt;				//current player cnt
	int m_nMatchSeatWay;			//random or by order to give seat number
	int m_nStatus;					//room's status

	Hero TenSelectHero[10];
	//functions
public:
//	Room(int roomid,ERoomType type, const std::string& name, EMatchSeatWay eway);
	virtual ~Room();

	int EnterRoom(Player* player);
	int QuitRoom(Player* player);
	int Broadcast(PPacket* pkt);
	int Unicast(Player* player, PPacket* pkt);
	int Ready(Player* player);
	int CheckGameStart();
	

	//void Get(proto::game::Room* proom);
	//void Set(const proto::game::Room& proom);
	void SetTenSelectHero(const Json::Value& proom);
	void Get(Json::Value& proom);
	void Set(const Json::Value& proom);

	void reset();
protected:

private:

};


#endif

