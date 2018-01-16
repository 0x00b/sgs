/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.11
Description : include definitions and some headers
**************************************************/

#ifndef _SGSG_MAIN_H_
#define _SGSG_MAIN_H_

/* includes*/
#include "log.h"

/* global variables*/

enum SGSCMD
{
	/* */
	PLAYER_START = 0,		
	PLAYER_REGIST,			//player regist
	PLAYER_LOGIN,			//player login
	PLAYER_QUIT,			//player quit game
	PLAYER_GET_FRIENDS,		//player get his friends
	PLAYER_DELETE_FRIENDS,	//delete his friend
	PLAYER_ADD_FRIENDS,		//add firends

	PLAYER_MATCH_ROOM,		//player request match room
	PLAYER_MATCH_ROOM_FAST,	//player request match room fast,auto enter room
	PLAYER_ENTER_ROOM,		//player enter room 
	PLAYER_QUIT_ROOM,		//player quit room
	PLAYER_SEARCH_ROOM,		//player search room by room id 
	PLAYER_READY,			//player get ready
	PLAYER_SELECT_GAME_MODE,//player select game mode
	PLAYER_GET_GAME_MODE,	//player get game mode
	PLAYER_CREATE_ROOM,		//player create a room
	
	/* GAME CMD */
	GAME_START = 1000,
};

#endif // !_SGSG_MAIN_H_
