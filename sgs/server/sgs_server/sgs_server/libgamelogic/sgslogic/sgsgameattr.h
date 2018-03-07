/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.24
Description : SGSCard
**************************************************/

#ifndef _SGS_SGS_GAME_ATTR_H_
#define _SGS_SGS_GAME_ATTR_H_

#include "../gameattr.h"
#include <vector>

class Hero;

class SGSGameAttr : public GameAttr
{
  /*varibles*/
private:
protected:
public:
  std::shared_ptr<Hero> m_pHero;
  std::vector<std::shared_ptr<Hero>> m_vHeros;

  int m_nBlood = 0;
  bool m_bSelectedHero;
  int m_nToMeCard;
  int m_nStatus;
  int m_nDiscardCnt;
  
  virtual void Reset();

  /*functions*/
public:
  SGSGameAttr();
  virtual ~SGSGameAttr();

protected:
private:
};

#endif