#include "Do_function.h"
#include "AppDelegate.h"


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
	log("123");
	if (0 == pkt["code"].asInt())
	{
	//	if(u_player.)
		u_room.Set(pkt);
		u_room.m_stNewPlayer = pkt["player"].asString();
		if (u_room.m_stNewPlayer == u_player.m_stAccount) {
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
				Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, ReadyHome::createScene()));
			});
		}
		else {
			((ReadyHome*)u_player.MyCurrentScene)->UpdateReadyHome();
		}
	}
	else
	{
		;
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


void Do_function::PLAYER_GET_GAME_MODE_UC(Json::Value &pkt, int cmd) {
	;
}