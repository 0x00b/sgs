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
	std::map<int, Player*> m_mPlayers;
	std::map<int, Room*>   m_mTables;
	
	ev_io m_iAccept;

	int m_nListenfd;
	int m_nStatus;

protected:

public:

//functions
public:
	Game();
	virtual ~Game();
	int StartUp();

	int UserRegist();
	int UserLogin();
	int UserQuit(Player* player);

	int MatchRoom(Player* player);
	int SelectGameMode();
	int GetGameMode();
	int CreateRoom();
	int EnterRoom(int roomId);
	int EnterRoomFast();
	int SearchRoom(int roomId);

	int Broadcast(std::string stMsg);
	int Unicast(Player* player,std::string stMsg);
protected:
	
private:
	int Listen();
	static void Accept_cb(struct ev_loop *loop, struct ev_io *w, int revents);
};

#endif