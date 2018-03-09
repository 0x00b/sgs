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



/*************************************************
* Class		: SGSGameAttr
* Description	: 每个玩家包含一个游戏属性类，这个类保存了玩家游戏逻辑需要的所有信息
* Author		: lijun
* Create Date	: 2018.1.17
**************************************************/
class SGSGameAttr : public GameAttr
{
  /*varibles*/
private:
protected:
public:
  std::shared_ptr<Hero> m_pHero;  //出场的武将
  std::vector<std::shared_ptr<Hero>> m_vHeros;//选择的武将

  int m_nBlood;       //保存最大血量值
  int m_nToMeCard;    //别人对我使用的牌
  int m_nStatus;      //状态，打牌，弃牌
  int m_nDiscardCnt;  //弃牌的数量
  bool m_bSelectedHero;//是否选择了英雄
  bool m_bCanSha;     //能否出杀
  int m_nAttackDistance;//攻击距离
  int m_nDeffeceDistance;//防御距离

  std::list<int> m_lstEquip;//装备
  
  virtual void Reset();

  /*functions*/
public:
  SGSGameAttr();
  virtual ~SGSGameAttr();

protected:
private:
};

#endif