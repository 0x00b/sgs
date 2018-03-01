#ifndef __FIGHTMAIN_SCENE_H__
#define __FIGHTMAIN_SCENE_H__

#include "model/include_all.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;

class FightMain : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FightMain);
};

#endif // __FIGHTMAIN_SCENE_H__
