/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description :
**************************************************/

#ifndef _SGS_PLAYER_H_
#define _SGS_PLAYER_H_

#include "include.h"
#include "client.h"
#include "protoco/appproto.pb.h"

class Room;

enum EPlayerStatus
{
	ST_PLAYER_OFFLINE = 0,
	ST_PLAYER_ONLINE,
	ST_PLAYER_BUSY,
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
	Client m_iClient;		

	//objects
	Room*  m_pRoom;						//entered room

	std::string m_stAccount;			//account
	std::string m_stPasswd;				//password
	std::string m_stName;				//player's name
	std::string m_stAvatar;				//head picture
	std::string m_stRegistDate;			//
	std::string m_stRemark;				//
										//ints
	int m_nID;
	int m_nExp;							//experience
										//
	short m_sLevel;						//level
										//
	char m_chSex;						//sex
	char m_nStatus;						//player's status
	char m_nGameStatus;					//player's gaming status

	//functions
public:
	Player();
	Player(int fd, std::string stIP);
	virtual ~Player();
	void Init();

	int ReqRegist();
	int ReqLogin();
	int ReqUpdatePwd();
	int ReqGetInfo();
	int ReqGetFriends();
	int ReqAddFriends();
	int ReqDeleteFriends();
	int GetInfoByID();
	int Send(std::shared_ptr<PPacket>& pkt);

	int UpdateState(EPlayerStatus status);
	
	std::string& GetProtoMsg();

	virtual int BeforeDo();
	virtual int Do();
	virtual int AfterDo();
protected:

private:
	void Set(const proto::game::Player& player);
	void Get(proto::game::Player* player);
	int CheckAccount();
	int CheckPasswd();
	int Regist();
	int Login();
	int GetFriends(std::list<std::shared_ptr<Player>>& list);
	int AddFriends(int idfriend);
	int DeleteFriends(int idfriend);
};

#endif