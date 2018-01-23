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
class PPacket;

class Game
{
//variables
private:
	std::map<int, Player*> m_mPlayers;
	std::map<int, Room*>   m_mRooms;
	
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
	int UserQuit(Player* player);
	int GetNewRoomID();

	int ReqMatchRoom(Player* player);
	int ReqSelectGameMode(Player* player);
	int ReqGetGameMode(Player* player);
	int ReqCreateRoom(Player* player);
	int	ReqEnterRoom(Player* player);
	int	ReqQuitRoom(Player* player);
	int ReqEnterRoomFast(Player* player);
	int ReqSearchRoom(Player* player);

	int Broadcast(PPacket* pkt);
	int Unicast(Player* player,PPacket* pkt);

	const Player* GetOLPlayer(int playerid);
protected:
	
private:
	int Listen();
	static void Accept_cb(struct ev_loop *loop, struct ev_io *w, int revents);
	
};

#endif