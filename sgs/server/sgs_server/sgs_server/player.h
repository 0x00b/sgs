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

class Player
{
	//variables
private:
	/*
	cards
	cards cnt
	*/
	//objects
	Client m_iClient;		
	Room*  m_pRoom;						//entered room

	std::string m_stAccount;			//account
	std::string m_stPasswd;				//password
	std::string m_stName;				//player's name
	std::string m_stAvatar;				//head picture
	//ints
	int m_sExp;							//experience
	//
	short m_sLevel;						//level
	//
	char m_chSex;						//sex
	char m_nStatus;						//player's status
	char m_nGameStatus;					//player's gaming status

protected:

public:

	//functions
public:
	Player();
	virtual ~Player();

	int GetFriends();
	int AddFriends();
	int DeleteFriends();
	int QuitRoom();

	virtual int DoOperation();
protected:

private:

};

#endif