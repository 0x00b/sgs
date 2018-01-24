/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.12
Description : GameLogic
**************************************************/

#ifndef _SGS_GAMELOGIC_H_
#define _SGS_GAMELOGIC_H_

#include <map>

class Player;
class Room;

class GameLogic
{
	/*varibles*/
private:
	std::map<Player*, int> m_mPlayer;
	Room* m_pRoom;
protected:

public:

	/*functions*/
public:
	GameLogic();
	virtual ~GameLogic();
	
	void Init(Room* proom);
	int Enter(Player* player);
	int Leave(Player* player);
	int GetSeatID(Player* player);

	virtual int Do(Player* player) = 0;
	virtual int GameStart() = 0;

protected:

private:
};

#endif