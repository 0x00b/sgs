/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.12
Description : GameLogic
**************************************************/

#ifndef _SGS_GAMELOGIC_H_
#define _SGS_GAMELOGIC_H_

#include <map>
#include <memory>
#include <list>

#include "card.h"

class Player;
class Room;
class GameAttr;

class GameLogic
{
	/*varibles*/
private:

protected:
	static std::list<std::shared_ptr<Card>> g_lstCards;
	std::map<Player*, std::shared_ptr<GameAttr>> m_mPlayer;	//all player in the room, one player match a GameAttr
	std::list<std::shared_ptr<Card>> m_lstCards;			//all card

	Room* m_pRoom;	//this logic belongs to the room


public:

	/*functions*/
public:
	GameLogic();
	virtual ~GameLogic();
	
	virtual void Init(Room* proom);
	virtual int Enter(Player* player) = 0;
	virtual int Leave(Player* player);

	int GetSeatID(Player* player);

	virtual int Do(Player* player) = 0;
	virtual int GameStart() = 0;

protected:

private:
};

#endif