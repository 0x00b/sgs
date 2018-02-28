#pragma once

#include "../Classes/model/include_all.h"

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

