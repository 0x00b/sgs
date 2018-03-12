#pragma once

#include "../Classes/model/include_all.h"
#include "HelloWorldScene.h"
#include "../Classes/Home/ReadyHomeScene2.h"
#include "../Classes/Fight/FightMainScene.h"
#include "../Classes/SelectHero2Layer/SelectHero2Layer.h"
#include "Login/LoginScene.h"

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
	static void GAME_START(Json::Value &pkt, int cmd);
	static void GAME_SELECT_CARD_BC(Json::Value &pkt, int cmd);
	static void GAME_SELECT_HERO_BC(Json::Value &pkt, int cmd);
	static void GAME_DEAL_BC(Json::Value &pkt, int cmd);
	static void GAME_OUT_CARD_BC(Json::Value &pkt, int cmd);
	static void GAME_PLAY_CARD_BC(Json::Value &pkt, int cmd);
	static void GAME_DISCARD_UC(Json::Value &pkt, int cmd);
	static void GAME_DISCARD_BC(Json::Value &pkt, int cmd);
	static void GAME_CANCEL_OUT_CARD_BC(Json::Value &pkt, int cmd);
	static void GAME_CHANGE_BLOOD(Json::Value &pkt, int cmd);
	static void GAME_GAME_END(Json::Value &pkt, int cmd);
	static void GAME_CHAT_BC(Json::Value &pkt, int cmd);
	static void GAME_EQUIP_BC(Json::Value &pkt, int cmd);
};