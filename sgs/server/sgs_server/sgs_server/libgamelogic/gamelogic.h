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
#include <vector>

#include "sgslogic/sgscard.h"

class Player;
class Room;
class SGSGameAttr;

class GameLogic
{
	/*varibles*/
private:

protected:

	std::map<int, std::shared_ptr<SGSGameAttr>> m_mPlayer;	//all player in the room, one player match a GameAttr
	std::vector<std::shared_ptr<SGSCard>> m_vCards;			//current all card

	Room* m_pRoom;	//this logic belongs to the room

public:
	static const std::shared_ptr<SGSCard>* const g_lstCards; //must initial this into your cards

	/*functions*/
public:
	GameLogic();
	virtual ~GameLogic();
	
	virtual void Init() = 0;
	virtual void SetRoom(Room* proom);
	virtual int Enter(Player* player) = 0;
	virtual int Leave(Player* player);

	int GetSeatID(Player* player);

	virtual int Do(Player* player) = 0;
	virtual int GameStart() = 0;

protected:

private:
};

#endif