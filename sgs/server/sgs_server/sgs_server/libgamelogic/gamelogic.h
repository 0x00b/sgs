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

class GameLogic
{
	/*varibles*/
private:
	std::map<int, Player*> m_mPlayer;
protected:

public:

	/*functions*/
public:
	GameLogic();
	virtual ~GameLogic();

	virtual int Do(Player* player) = 0;

protected:

private:
};

#endif