#include "Do_function.h"
#include "AppDelegate.h"
#include "../Classes/model/sgscard.h"
#include "Fight\FightMainScene.h"


Do_function::Do_function()
{
}


Do_function::~Do_function()
{
}

void Do_function::PLAYER_LOGIN_UC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())
	{
		u_player.Set(pkt[SJPROTO[E_Player]]);
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, HelloWorld::createScene()));
		});
	}
	else
	{
		MessageBox("login failed!", "");
	};
}


void Do_function::PLAYER_CREATE_ROOM_UC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())
	{
		u_room.Set(pkt);
		if (!u_room.m_lstPlayers.empty())
		{
			u_player.m_nSeatId = u_room.m_lstPlayers.front().m_nSeatId;
		}
		else
		{
			log("no player");
		}
	//	u_player.m_nSeatId = u_room.m_lstPlayers
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
			u_player.MyCurrentScene = ReadyHome::createScene();
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, u_player.MyCurrentScene));
		});
	}
	else
	{
		;
	}
}

/*
log(p.body.c_str());
log(root["code"].asString().c_str());


//	log("%d", root["code"].asInt());
*/

void Do_function::PLAYER_ENTER_ROOM_BC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())	//成功
	{
		u_room.Set(pkt);
		u_room.m_stNewPlayer = pkt["player"].asString();
		if (u_room.m_stNewPlayer == u_player.m_stAccount) {

			for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
			{
				if (it->m_stAccount == u_player.m_stAccount)
				{
					u_player.m_nSeatId = it->m_nSeatId;
				}
			}

			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				u_player.MyCurrentScene = ReadyHome::createScene();
				Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, u_player.MyCurrentScene));
			});
		}
		else {
			((ReadyHome*)u_player.MyCurrentScene)->UpdateReadyHome();
		}
	}
	else if(4 == pkt["code"].asInt())	//不存在房间
	{
		MessageBox("can't find home","findhome");
	}
	else if (4 == pkt["code"].asInt()) {	//房间人数已满
		MessageBox("home if full", "findhome");
	}
}

void Do_function::PLAYER_READY_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt())
	{
	//	u_player.Set(pkt[SJPROTO[E_Player]]);
	//	Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
	//		Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, HelloWorld::createScene()));
	//	});
	}
	else
	{
		MessageBox("login failed!", "");
	};
}


int heroid[10];
void Do_function::GAME_START(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt())
	{
		int i;
		for (i = 0; i < 10; i++)
		{
			Json::Value v = pkt["hero"][i];
			heroid[i]= v["idhero"].asInt();
		}
		u_room.m_nStatus = 2;
		u_room.SetTenSelectHero(pkt);
	//	u_room.TenSelectHero;
	//	MessageBox(u_room.TenSelectHero[0].name);
		log("1231222222222222222222222222222222222\n");
		log("1231222222222222222222222222222222222\n country:\n");
		log(u_room.TenSelectHero[0].country);
		log("123222221111111111111111111111111111\n");
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]() {    //idhero
		u_player.MyCurrentScene = FightMain::createScene();  //把游戏界面给程序 		创建游戏界面
		// 把10个武将给放上去
		(((FightMain *)u_player.MyCurrentScene)->selectHero)->ShowHero(heroid);
		Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, u_player.MyCurrentScene));
	});
	}
	else
	{
		MessageBox("enter room failed!", "");
	};
}

void Do_function::PLAYER_GET_GAME_MODE_UC(Json::Value &pkt, int cmd) {
	;
}

void Do_function::GAME_SELECT_CARD_BC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())
	{
		//
		Layer *layer = (Layer*)u_player.MyCurrentScene->getChildByName("selectHero");
		layer->setVisible(false);
	}
	else
	{
		;
	}
}

void Do_function::GAME_DEAL_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt())
	{
		int u_seatid = pkt["seatid"].asInt();
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (it->m_nSeatId == u_seatid)
			{
				//u_player.m_nSeatId = it->m_nSeatId;
				int i;
				Json::Value & cards = pkt["cards"];
				for (i = 0; i<cards.size(); i++)
				{
					Json::Value v = cards[i];
					SGSCard *a = new SGSCard(v.asInt());
					it->m_oGameAttr.m_lstPlayerCards.push_back(std::shared_ptr<SGSCard>(a));
				}
				break;
			}
		}
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {	//更新手牌
			((FightMain *)u_player.MyCurrentScene)->UpdateHandCard();
		});
		//座位号
	}
	else
	{
		MessageBox("deal failed!", "");
	};
}

void Do_function::GAME_SELECT_HERO_BC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())
	{
		//
		Layer *layer = (Layer*)u_player.MyCurrentScene->getChildByName("selectHero");
	//	
		int u_seatid = pkt["seatid"].asInt();
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (it->m_nSeatId == u_seatid)
			{
				//u_player.m_nSeatId = it->m_nSeatId;
				*it->m_oGameAttr.m_pHero = u_room.TenSelectHero[ pkt.get("idhero", 0).asInt()-1];
				break;
			}
		}
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
			((FightMain*)(u_player.MyCurrentScene))->InitHeroInfo();	//更新选中的武将
		});
		if (u_seatid == u_player.m_nSeatId)
		{
			//((FightMain*)u_player.MyCurrentScene)->selectHero->removeFromParentAndCleanup(true);
			layer->setVisible(false);
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}
}


void Do_function::GAME_OUT_CARD_BC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())
	{
		//
		int card_num = pkt["card"].asInt();
		int u_seatid = pkt["seatid"].asInt();
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{//std::list<std::shared_ptr<SGSCard>> m_lstPlayerCards; //all card
			if (it->m_nSeatId == u_seatid)
			{
				for (std::list<std::shared_ptr<SGSCard>>::iterator it_card = it->m_oGameAttr.m_lstPlayerCards.begin(); it_card != it->m_oGameAttr.m_lstPlayerCards.end();)
				{
					if ((*it_card)->card()==card_num)
					{
						it_card = it->m_oGameAttr.m_lstPlayerCards.erase(it_card);
						if (u_player.m_nSeatId == u_seatid)
						{
							Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
								((FightMain *)u_player.MyCurrentScene)->UpdateHandCard();
							});
						}
						break;
					}
					else
						++it_card;
				}
				break;
			}
			else {

			}
		}
	}
	else
	{
		log("failed");
	}
}

void Do_function::GAME_PLAY_CARD_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt()) {
		if (pkt["seatid"] == u_player.m_nSeatId) {
			int i;
			Json::Value & cards = pkt["cards"];
			for (i = 0; i<cards.size(); i++)
			{
				SGSCard *a = new SGSCard(cards[i].asInt());
				u_player.m_oGameAttr.m_lstPlayerCards.push_back(std::shared_ptr<SGSCard>(a));
			}
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				((FightMain *)u_player.MyCurrentScene)->UpdateHandCard();
				((FightMain *)u_player.MyCurrentScene)->ShowMyBtnAndTimer();
			});
		}
		else {
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				((FightMain *)u_player.MyCurrentScene)->HideMyBtnAndTimer();
				((FightMain *)u_player.MyCurrentScene)->ShowEnemyTimer();
			});
		}
	}
}