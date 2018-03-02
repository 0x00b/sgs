#ifndef _SGS_SGS_GAME_LOGIC_H_
#define _SGS_SGS_GAME_LOGIC_H_

#include "../gamelogic.h"

class SGSGameLogic : public GameLogic
{
  public:
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