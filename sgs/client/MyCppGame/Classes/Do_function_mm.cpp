#include "Do_function.h"
#include "AppDelegate.h"

void Do_function::PLAYER_REGIST_UC(Json::Value &pkt, int cmd){

}

void Do_function::PLAYER_QUIT_ROOM_BC(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt())
	{
		if (pkt[SJPROTO[E_Player]][SPlayer[EPlayer_account]].asString() == u_player.m_stAccount) {
			u_room.reset();
		}
		else {
			for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
			{
				if ((*it).m_stAccount == pkt[SJPROTO[E_Player]][SPlayer[EPlayer_account]].asString()) {
					u_room.m_lstPlayers.erase(it);
					break;
				}
			}
			if(u_room.m_nStatus < 2)
				((ReadyHome*)u_player.MyCurrentScene)->UpdateReadyHome();
		}
		/*u_room.Set(pkt);
		u_room.m_stNewPlayer = pkt["player"].asString();
		if (u_room.m_stNewPlayer == u_player.m_stAccount) {
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, ReadyHome::createScene()));
			});
		}
		else {
			((ReadyHome*)u_player.MyCurrentScene)->UpdateReadyHome();
		}*/
	}
	else
	{

	}
}

void Do_function::PLAYER_SEARCH_ROOM_UC(Json::Value &pkt, int cmd) {

	if (0 == pkt["code"].asInt())
	{	//寻找房间是单播 如果寻找房间成功 再发一条进入该房间的消息?
		/*u_room.Set(pkt);
		u_room.m_stNewPlayer = pkt["player"].asString();
		if (u_room.m_stNewPlayer == u_player.m_stAccount) {
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, ReadyHome::createScene()));
			});
		}
		else {
			((ReadyHome*)u_player.MyCurrentScene)->UpdateReadyHome();
		}*/
	}
	else
	{
		;
	}
}



