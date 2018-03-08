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

	int m_nCurrOutSeat;
	int m_nCurrPlayerSeat;
	int m_nPlayerSeat;
	SGSCard m_oLastCard;
	int m_nStatus;
	
	enum GM_STATUS
	{
		PLAYER_NONE,
		PLAYER_PLAY_CARD,
		PLAYER_DISCARD
	};

	ev_timer play_timer;
	ev_tstamp play_timer_stamp;

	ev_timer discard_timer;
	ev_tstamp discard_timer_stamp;

public:
	SGSGameLogic();
	virtual ~SGSGameLogic();
	virtual int Do(Player *player);
	virtual int GameStart();
	virtual int Enter(Player *player);

	static void play_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents);
	static void discard_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents);

	virtual void Reset();
	virtual void Init();
	
	bool HasSeat(int seatid);

	void InitCard();

	void EnsureRoles();
	void RandomCard();

	int Do2PStart(Json::Value &root);
	int Do6PStart(Json::Value &root);

	int StartDeal();//开始发牌
	int Deal(SGSGameAttr& player, Json::Value& v, int cnt);//给player发牌
	int PlayCardUC(int seat);
	int DisCardUC(Player* player);

	int ReqPlayCard(Player *player);
	int ReqDiscard(Player *player);
	int ReqUseSkill(Player *player);
	int ReqCancelOutCard(Player *player);
	int ReqSelectCard(Player *player);
	int ReqSelectHero(Player *player);

	int CanPlayCard(Player* player ,int card);

	int DealCard(int card, int seat, Json::Value& root);

	int DealCard_Tao(int seat, int to_seat);
	int DealCard_Sha(int seat, int to_seat);
	int DealCard_Shan(int seat);


private:
};

#endif