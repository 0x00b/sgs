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
	if (0 == pkt["code"].asInt())	//成功
	{
		u_room.Set(pkt);
		u_room.m_stNewPlayer = pkt["player"].asString();
		if (u_room.m_stNewPlayer == u_player.m_stAccount) {
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

void Do_function::GAME_START(Json::Value &pkt, int cmd) {
	if (0 == pkt["code"].asInt())
	{
		int heroid[10];
		int i;
		for (i = 0; i < 10; i++)
		{
			Json::Value v = pkt["hero"][i];
			heroid[i]= v["idhero"].asInt();
		}
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