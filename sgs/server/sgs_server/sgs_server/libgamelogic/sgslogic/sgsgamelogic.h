#ifndef _SGS_SGS_GAME_LOGIC_H_
#define _SGS_SGS_GAME_LOGIC_H_

#include "../gamelogic.h"
#include "hero.h"
#include <vector>
#include "../../include/libev/ev.h"

class SHero
{
public:
	SHero(const std::shared_ptr<Hero> &hero);
	bool m_bSelected;
	std::shared_ptr<Hero> m_pHero;
};

class SGSGameLogic : public GameLogic
{
public:
	static const int P2P_CAN_SELECT_HERO_CNT = 10;
	static const int P2P_HERO_CNT = 2;
	std::vector<std::shared_ptr<SHero>> m_vSelcectHero;
	int m_nSelected; //已经选择的英雄
	Player* m_pCurrPlayer;

	ev_timer play_timer;
	ev_tstamp play_timer_stamp;

public:
	SGSGameLogic();
	virtual ~SGSGameLogic();
	virtual int Do(Player *player);
	virtual int GameStart();
	virtual int Enter(Player *player);

	static void play_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents);

	virtual void Reset();
	virtual void Init();
	
	bool HasSeat(int seatid);

	void InitCard();

	void EnsureRoles();
	void RandomCard();

	int Do2PStart(Json::Value &root);
	int Do6PStart(Json::Value &root);

	int StartDeal();//开始发牌
	int Deal(Player* player);//给player发牌
	int PlayCardUC(Player* player);

	int ReqPlayCard(Player *player);
	int ReqDiscard(Player *player);
	int ReqUseSkill(Player *player);
	int ReqCancelOutCard(Player *player);
	int ReqSelectCard(Player *player);
	int ReqSelectHero(Player *player);

private:
};

#endif