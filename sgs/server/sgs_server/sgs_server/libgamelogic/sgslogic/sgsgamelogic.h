#ifndef _SGS_SGS_GAME_LOGIC_H_
#define _SGS_SGS_GAME_LOGIC_H_

#include "../gamelogic.h"
#include "hero.h"
#include <vector>

class SHero
{
public:
	SHero(const std::shared_ptr<Hero>& hero); 
	bool m_bSelected;
	std::shared_ptr<Hero> m_pHero;
};

class SGSGameLogic : public GameLogic
{
  public:
    static const int P2P_CAN_SELECT_HERO_CNT = 10;
    static const int P2P_HERO_CNT = 6;
		std::vector<std::shared_ptr<SHero>> m_vSelcectHero;
		int m_nSelected;	//已经选择的英雄
		int m_nCurrPlayerID;

  public:
	SGSGameLogic();
	virtual ~SGSGameLogic();
	virtual int Do(Player *player);
	virtual int GameStart();
	virtual int Enter(Player *player);
	
	virtual void Init();

	void InitCard();

	void EnsureRoles();
	void RandomCard();

	int Do2PStart(Json::Value& root);
	int Do6PStart(Json::Value& root);

	int ReqOutCard(Player *player);
	int ReqAbandonCard(Player *player);
	int ReqUseSkill(Player *player);
	int ReqCancelOutCard(Player *player);
	int ReqSelectCard(Player *player);
	int ReqSelectHero(Player *player);

  private:
};

#endif