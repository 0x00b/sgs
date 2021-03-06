/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.24
Description : SGSCard
**************************************************/

#ifndef _SGS_SGS_GAME_ATTR_H_
#define _SGS_SGS_GAME_ATTR_H_

#include "gameattr.h"

class Hero;

class SGSGameAttr: public GameAttr
{
    /*varibles*/
  private:

  protected:
  public:
    std::shared_ptr<Hero> m_pHero;
    int m_nMaxBlood = 0;

    /*functions*/
  public:
    SGSGameAttr();
    virtual ~SGSGameAttr();

  protected:
  
  private:
};

#endif