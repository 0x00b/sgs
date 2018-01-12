/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description : 
**************************************************/
#ifndef _SGS_GAME_H_
#define _SGS_GAME_H_

#include "include.h"

class Player;
class Room;

class Game
{
//variables
private:
	std::list<Player*> m_iPlayers;
	std::list<Room*>   m_iTables;
	int m_nStatus;
protected:

public:

//functions
public:
	Game();
	~Game();
	int StartUp();

	int UserRegist();
	int UserLogin();
	int UserQuit();

	int MatchRoom();
	int SelectGameMode();
	int GetGameMode();
	int CreateRoom();
	int EnterRoom();
	int EnterRoomFast();
	int SearchRoom();

	int Broadcast();
protected:
	
private:

};

#endif