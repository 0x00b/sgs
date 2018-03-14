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



/*************************************************
* Class		: SGSGameLogic
* Description	: 游戏逻辑处理类
* Author		: lijun
* Create Date	: 2018.1.17
**************************************************/
class SGSGameLogic : public GameLogic
{
public:
	static const int P2P_CAN_SELECT_HERO_CNT = 10;
	static const int P2P_HERO_CNT = 2;
	std::vector<std::shared_ptr<SHero>> m_vSelcectHero;//可选择的武将
	int m_nSelected; 				//已经选择的英雄数量

	int m_nCurrOutSeat;				//当前出牌的玩家
	int m_nCurrPlayerSeat;			//当前回合是谁的
	//int m_nPlayerSeat;				
	SGSCard m_oLastCard;			//当前回合的牌
	int m_nStatus;					//状态是
	int m_nFistOutCard;
	
	enum GM_STATUS
	{
		PLAYER_NONE,				//玩家无操作
		PLAYER_PLAY_CARD,			//玩家打牌
		PLAYER_DISCARD				//弃牌阶段
	};

	ev_timer play_timer;			//打牌定时器
	ev_tstamp play_timer_stamp;		

	ev_timer discard_timer;			//弃牌定时器
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
	virtual int Leave(Player* player);
	
	bool HasSeat(int seatid);

	void InitCard();

	void EnsureRoles();
	void RandomCard();

	int Do2PStart(Json::Value &root);
	int Do6PStart(Json::Value &root);

	int StartDeal();//开始发牌
	int Deal(SGSGameAttr& player, Json::Value& v, int cnt);//给player发牌
	int PlayCardUC(int seat, int deal = 0);
	int DisCardUC(Player* player);
	int ChangeBloodBC(int seat, int blood);
	int CanContinuePlayCard(int seat);
	int GameEnd(int winseat);

	int ReqPlayCard(Player *player);
	int ReqDiscard(Player *player);
	int ReqUseSkill(Player *player);
	int ReqCancelOutCard(Player *player);
	int ReqSelectCard(Player *player);
	int ReqSelectHero(Player *player);
	int ReqChat(Player *player);
	

	int CanPlayCard(Player* player ,int card);

	int DealCard(int card, int seat, Json::Value& root);
	int DealCard_Tao(int seat, int to_seat);
	int DealCard_Sha(int seat, int to_seat);
	int DealCard_Shan(int seat, int to_seat);
	int DealCard_WuZhongSY(int seat);
	int DealCard_ZhuGeLL(int seat);
	int DealCard_GuoHeCQ(int seat, int to_seat);
	

private:
};

#endif