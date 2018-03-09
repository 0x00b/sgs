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
			//log("no player");
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
	if (0 == pkt["code"].asInt())	//�ɹ�
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
	else if(4 == pkt["code"].asInt())	//�����ڷ���
	{
		MessageBox("can't find home","findhome");
	}
	else if (4 == pkt["code"].asInt()) {	//������������
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
		/*log("1231222222222222222222222222222222222\n");
		log("1231222222222222222222222222222222222\n country:\n");
		log(u_room.TenSelectHero[0].country);
		log("123222221111111111111111111111111111\n");*/
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]() {    //idhero
		u_player.MyCurrentScene = FightMain::createScene();  //����Ϸ��������� 		������Ϸ����
		// ��10���佫������ȥ
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
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {	//��������
			((FightMain *)u_player.MyCurrentScene)->UpdateHandCard();
		});

		//����������
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {	//���¶���������
			((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(0, pkt["card_cnt"].asInt());
			((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(1, pkt["card_cnt"].asInt());
		});

		//��λ��

	}
	else
	{
		log("GAME_DEAL_BC %d", pkt["code"].asInt());
	}
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
				it->m_oGameAttr.m_nMaxBlood = it->m_oGameAttr.m_pHero->blood;
				break;
			}
		}
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
			((FightMain*)(u_player.MyCurrentScene))->InitHeroInfo();	//����ѡ�е��佫
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
		//log("GAME_SELECT_HERO_BC %d", pkt["code"].asInt());
	}
}


void Do_function::GAME_OUT_CARD_BC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())
	{
		//
		int card_num = pkt["card"].asInt();
		int u_seatid = pkt["seatid"].asInt();
		switch (SGSCard::func(card_num))
		{
		case SGSCard::CARD_SHA:
		if (u_seatid == u_player.m_nSeatId)
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				((FightMain *)u_player.MyCurrentScene)->show_sha(0);
			});
		}
		else
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				((FightMain *)u_player.MyCurrentScene)->show_sha(1);
			});
		}
		break;
		case SGSCard::CARD_SHAN:
			if (u_seatid == u_player.m_nSeatId)
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
					((FightMain *)u_player.MyCurrentScene)->show_shan(0);
				});
			}
			else
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
					((FightMain *)u_player.MyCurrentScene)->show_shan(1);
				});
			}
			; break;
		case SGSCard::CARD_TAO:
			if (u_seatid == u_player.m_nSeatId)
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
					((FightMain *)u_player.MyCurrentScene)->show_tao(0);
				});
			}
			else
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
					((FightMain *)u_player.MyCurrentScene)->show_tao(1);
				});
			}
			; break;
		default:
			break;
		}
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
		//����������
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (u_player.m_nSeatId == pkt["seatid"].asInt())
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() { //�����ҵ�������
					((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(0, pkt["card_cnt"].asInt());
				});
				break;
			}
			else {
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {	//���¶���������
					((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(1, pkt["card_cnt"].asInt());
				});
				break;
			}
		}
	}
	else
	{
		log("GAME_OUT_CARD_BC %d", pkt["code"].asInt());
	}
}

void Do_function::GAME_PLAY_CARD_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt()) {
		if (pkt["seatid"] == u_player.m_nSeatId) {
			int i;
			Json::Value & cards = pkt["cards"];
			for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
			{//std::list<std::shared_ptr<SGSCard>> m_lstPlayerCards; //all card
				if (it->m_nSeatId == u_player.m_nSeatId)
				{
					for (i = 0; i < cards.size(); i++)
					{
						SGSCard *a = new SGSCard(cards[i].asInt());
						(*it).m_oGameAttr.m_lstPlayerCards.push_back(std::shared_ptr<SGSCard>(a));
					}
					break;
				}
			}
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				((FightMain *)u_player.MyCurrentScene)->UpdateHandCard();
				((FightMain *)u_player.MyCurrentScene)->HideEnemyTimer();
				((FightMain *)u_player.MyCurrentScene)->ShowMyBtnAndTimer();
			});
			((FightMain *)u_player.MyCurrentScene)->setStatus(1);	//���Ե��һ����
			((FightMain *)u_player.MyCurrentScene)->setStage(1);	//��ǰ���ڳ��ƽ׶�
		}
		else {
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				((FightMain *)u_player.MyCurrentScene)->HideMyBtnAndTimer();
				((FightMain *)u_player.MyCurrentScene)->ShowEnemyTimer();
			});
			((FightMain *)u_player.MyCurrentScene)->setStatus(0);	//���ܵ����
			((FightMain *)u_player.MyCurrentScene)->setStage(3);	//��ǰ���ڵȴ�״̬
		}
		//����������
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (u_player.m_nSeatId == pkt["seatid"].asInt())
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() { //�����ҵ�������
					((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(0, pkt["card_cnt"].asInt());
				});
				break;
			}
			else {
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {	//���¶���������
					((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(1, pkt["card_cnt"].asInt());
				});
				break;
			}
		}
		//���µ�ǰ�׶�
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (u_player.m_nSeatId == pkt["seatid"].asInt())
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() { //�����ҵ�������
					((FightMain *)u_player.MyCurrentScene)->UpdateStageLab(CSGSTXT::GET("outcard"));
				});
			}
			else {
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {	//���¶���������
					((FightMain *)u_player.MyCurrentScene)->UpdateStageLab(CSGSTXT::GET("wait"));
				});
			}
		}
	}
	else
	{
		log("GAME_PLAY_CARD_BC %d", pkt["code"].asInt());
	}
}

void Do_function::GAME_DISCARD_UC(Json::Value &pkt, int cmd) {
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
		((FightMain *)u_player.MyCurrentScene)->ShowMyBtnAndTimer();
	});
	((FightMain *)u_player.MyCurrentScene)->setStatus(pkt["discard_cnt"].asInt());
	//log("%d",pkt["discard_cnt"].asInt());
	((FightMain *)u_player.MyCurrentScene)->setStage(2);

	//���µ�ǰ�׶�
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() { //�����ҵ�������
		((FightMain *)u_player.MyCurrentScene)->UpdateStageLab(CSGSTXT::GET("discard"));
	});
}

void Do_function::GAME_DISCARD_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt()) {
		//log("%d", pkt["cards"].size());
		if (pkt["seatid"].asInt() == u_player.m_nSeatId) {		//��������
			for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
			{
				if (it->m_nSeatId == pkt["seatid"].asInt())	//����б����ҵ���
				{
					for (int i = 0; i < pkt["cards"].size(); ++i) {
						for (std::list<std::shared_ptr<SGSCard>>::iterator it_card = it->m_oGameAttr.m_lstPlayerCards.begin(); it_card != it->m_oGameAttr.m_lstPlayerCards.end();)
						{
							if ((*it_card)->card() == pkt["cards"][i].asInt())
							{
								it_card = it->m_oGameAttr.m_lstPlayerCards.erase(it_card);
								break;
							}
							else
								++it_card;
						}
					}
					break;
				}
			}
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				((FightMain *)u_player.MyCurrentScene)->UpdateHandCard();
			});
		}else {	//�����������

		}
		//����������
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (u_player.m_nSeatId == pkt["seatid"].asInt())
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() { //�����ҵ�������
					((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(0, pkt["card_cnt"].asInt());
				});
				break;
			}
			else {
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {	//���¶���������
					((FightMain *)u_player.MyCurrentScene)->UpdateHandCardNum(1, pkt["card_cnt"].asInt());
				});
				break;
			}
		}
	}
	else
	{
		log("GAME_DISCARD_BC %d", pkt["code"].asInt());
	}
}

void Do_function::GAME_CANCEL_OUT_CARD_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt()) {
		
	}
}

void Do_function::GAME_CHANGE_BLOOD(Json::Value &pkt, int cmd) {

	int max_blood = 0;
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
	{
		if (it->m_nSeatId == pkt["seatid"].asInt())
		{
			max_blood = it->m_oGameAttr.m_nMaxBlood;
			break;
		}
	}

	if (pkt["seatid"].asInt() == u_player.m_nSeatId) {		//�ҵ�Ѫ���仯
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() { //�����ҵ�������
			((FightMain *)u_player.MyCurrentScene)->UpdateFightInfo(0, pkt["blood"].asInt(), max_blood);
		});
	}
	else {	//����Ѫ���仯
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() { //�����ҵ�������
			((FightMain *)u_player.MyCurrentScene)->UpdateFightInfo(1, pkt["blood"].asInt(), max_blood);
		});
	}
}

void Do_function::GAME_GAME_END(Json::Value &pkt, int cmd) {
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it) {
		if (pkt["seatid"].asInt() == u_player.m_nSeatId) {
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
				((FightMain *)u_player.MyCurrentScene)->GameEnd(0);
			});
		}
		else {
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
				((FightMain *)u_player.MyCurrentScene)->GameEnd(1);
			});
		}
	}
}

void Do_function::GAME_CHAT_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt()) {
		int seatid = pkt["seatid"].asInt();
		string message = pkt["message"].asString();
		string name;
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (it->m_nSeatId == seatid)
			{
				name = it->m_stAccount;
				break;
			}
		}
		message = name + ":" + message;
		int list_num = u_room.m_chat_message.size();
		if (list_num == 8)
		{
			u_room.m_chat_message.pop_front();
		}
		u_room.m_chat_message.push_back(message);
		((FightMain *)u_player.MyCurrentScene)->UpdateChat();
	}
	else
	{
		log("send failed!");
	}
}