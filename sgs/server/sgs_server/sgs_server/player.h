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

	int Regist();
	int Login();
	int GetInfo();
	int GetFriends();
	int AddFriends();
	int DeleteFriends();
	int QuitRoom();

	virtual int BeforeDo();
	virtual int Do();
	virtual int AfterDo();
protected:

private:

};

#endif