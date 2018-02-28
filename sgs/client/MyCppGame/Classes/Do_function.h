#pragma once

#include "../Classes/model/include_all.h"
#include "HelloWorldScene.h"
#include "../Classes/Home/ReadyHomeScene2.h"

class Do_function
{
public:
	Do_function();
	~Do_function();

public:
	static void PLAYER_REGIST_UC(Json::Value &pkt, int cmd);
	static void PLAYER_LOGIN_UC(Json::Value &pkt, int cmd);
	static void PLAYER_UPDATE_PWD_UC(Json::Value &pkt, int cmd);
	static void PLAYER_QUIT_UC(Json::Value &pkt, int cmd);
	static void PLAYER_GET_FRIENDS_UC(Json::Value &pkt, int cmd);
	static void PLAYER_DELETE_FRIENDS_UC(Json::Value &pkt, int cmd);
	static void PLAYER_ADD_FRIENDS_UC(Json::Value &pkt, int cmd);
	static void PLAYER_MATCH_ROOM_UC(Json::Value &pkt, int cmd);
	static void PLAYER_MATCH_ROOM_FAST_UC(Json::Value &pkt, int cmd);
	static void PLAYER_ENTER_ROOM_BC(Json::Value &pkt, int cmd);
	static void PLAYER_QUIT_ROOM_BC(Json::Value &pkt, int cmd);
	static void PLAYER_SEARCH_ROOM_UC(Json::Value &pkt, int cmd);
	static void PLAYER_READY_BC(Json::Value &pkt, int cmd);
	static void PLAYER_SELECT_GAME_MODE_UC(Json::Value &pkt, int cmd);
	static void PLAYER_GET_GAME_MODE_UC(Json::Value &pkt, int cmd);
	static void PLAYER_CREATE_ROOM_UC(Json::Value &pkt, int cmd);
};



