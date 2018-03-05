/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.24
Description : GameAttr
**************************************************/

#ifndef _SGS_GAMEATTR_H_
#define _SGS_GAMEATTR_H_

#include <list>
#include <memory>
#include "../player.h"

class SGSCard;

class GameAttr
{
  /*varibles*/
private:
protected:
public:

  std::list<std::shared_ptr<SGSCard>> m_lstPlayerCards; //all card
  Player* m_player;
  /*functions*/
public:
  GameAttr();
  virtual ~GameAttr();

protected:
private:
};

#endif