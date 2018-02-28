#pragma once

#include "../Classes/model/include_all.h"
#include "HelloWorldScene.h"

class Do_function
{
public:
	Do_function();
	~Do_function();

public:
	static void PLAYER_LOGIN_UC(Json::Value &pkt, int cmd);

};

