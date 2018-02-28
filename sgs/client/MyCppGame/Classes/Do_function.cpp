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
		u_room.Set(pkt[SJPROTO[E_Room]]);
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, ReadyHome::createScene()));
		});
	}
	else
	{
		;
	}
}

void Do_function::PLAYER_ENTER_ROOM_BC(Json::Value &pkt, int cmd)
{
	if (0 == pkt["code"].asInt())
	{
		u_room.Set(pkt[SJPROTO[E_Room]]);
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, ReadyHome::createScene()));
		});
	}
	else
	{
		;
	}
}

void Do_function::PLAYER_GET_GAME_MODE_UC(Json::Value &pkt, int cmd) {
	;
}