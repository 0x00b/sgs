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

class Card;

class GameAttr
{
  /*varibles*/
private:
protected:
public:
  int m_nSeatId;
  std::list<std::shared_ptr<Card>> m_lstPlayerCards; //all card

  /*functions*/
public:
  GameAttr();
  virtual ~GameAttr();

protected:
private:
};

#endif