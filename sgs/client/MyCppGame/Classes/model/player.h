/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description :
**************************************************/

#ifndef _SGS_PLAYER_H_
#define _SGS_PLAYER_H_

//#include "../Classes/model/"
#include <iostream>
#include "cocos2d.h"
#include "jsonproto/jsonproto.h"
#include "sgsgameattr.h"
#include "./libs/json/json.h"
class Room;

enum EPlayerStatus
{
	ST_PLAYER_OFFLINE = 0,
	ST_PLAYER_ONLINE,
	ST_PLAYER_BUSY,
};

enum EPlayerGmStatus
{
	ST_GM_PLAYER_NONE = 0,
	ST_GM_PLAYER_READY,
	ST_GM_PLAYER_PLAYING,
};

/*
*/
class Player
{
	//variables
private:
	/*
	cards
	cards cnt
	*/

protected:

public:
	//objects
	Room*  m_pRoom;						//entered room

	cocos2d::Scene* MyCurrentScene;

	std::string m_stAccount;			//account
	std::string m_stPasswd;				//password
	std::string m_stName;				//player's name
	std::string m_stAvatar;				//head picture
	std::string m_stRegistDate;			//
	std::string m_stRemark;				//
										//ints
//	int m_nHeroid;
	int m_nID;
	int m_nExp;							//experience
	int m_nSeatId;							//experience
										//
	short m_sLevel;						//level
										//
	char m_chSex;						//sex
	char m_nStatus;						//player's status
	char m_nGameStatus;					//player's gaming status
	SGSGameAttr m_oGameAttr;

	//functions
public:
	void Get(Json::Value& player);
	//Player(int fd, std::string stIP);
	//virtual ~Player();
	//void Init();

	//int GetInfoByID();
	//int Send(std::shared_ptr<PPacket>& pkt);

	//int UpdateState(EPlayerStatus status);
	//int EnterRoom(Room* room);
	//int QuitRoom();

	//std::string& GetProtoMsg();
	////void Set(const proto::game::Player& player);
	////void Get(proto::game::Player* player);
	void Set(const Json::Value& player);
	//
	//int SeatID();

	//int Regist();
	//int Login();
	//int GetFriends(std::list<std::shared_ptr<Player>>& list);
	//int AddFriends(int idfriend);
	//int DeleteFriends(int idfriend);
	//
	//int CheckAccount();
	//int CheckPasswd();
protected:

private:
};

#endif