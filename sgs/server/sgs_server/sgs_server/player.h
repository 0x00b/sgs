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

class Room;
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
	int m_sExp;							//experience
	//
	short m_sLevel;						//level
	//
	char m_chSex;						//sex
	char m_nStatus;						//player's status
	char m_nGameStatus;					//player's gaming status

protected:

public:
	Client m_iClient;		

	//functions
public:
	Player(int fd, std::string stIP);
	virtual ~Player();

	int ReqRegist();
	int ReqLogin();
	int ReqUpdatePwd();
	int ReqGetInfo();
	int ReqGetFriends();
	int ReqAddFriends();
	int ReqDeleteFriends();
	int ReqQuitRoom();
	int GetInfoByID();
	int Send(PPacket& pkt);

	virtual int BeforeDo();
	virtual int Do();
	virtual int AfterDo();
protected:

private:
	int Regist();
	int Login();
	int GetFriends();
	int AddFriends();
	int DeleteFriends();
};

#endif