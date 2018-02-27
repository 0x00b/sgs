#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

class pvp:public Layer
{
public:
	pvp();
	~pvp();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(pvp);

};

