#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class SelectHero2Layer :public Layer
{
public:
	SelectHero2Layer();
	~SelectHero2Layer();

	virtual bool init();

	void update(float dt);

	void setProgressTime(CCProgressTimer **progresstime1,Size win);

	CREATE_FUNC(SelectHero2Layer);
private:
	cocos2d::CCProgressTimer *progresstime1;

		

};

