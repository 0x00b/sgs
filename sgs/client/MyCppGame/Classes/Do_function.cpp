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
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, HelloWorld::createScene()));
		});
	}
	else
	{
		MessageBox("login failed!", "");
	};
}