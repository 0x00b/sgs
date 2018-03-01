#ifndef __READYHOME_SCENE_H__
#define __READYHOME_SCENE_H__

#include "SimpleAudioEngine.h"
#include "Mode/SelectModeScene.h"
#include "../Classes/model/include_all.h"

USING_NS_CC;
using namespace ui;

class ReadyHome : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(ReadyHome);

private:
	Button* btn_back;	//回退按钮
	//ImageView* img_table_bg1;	//一号位玩家
	//ImageView* img_table_bg2;	//二号位玩家
	ImageView* img_table_bg[8];	//玩家位
	Button* btn_ready;	//准备按钮

private:
	void DidBack(Ref* pSender, Widget::TouchEventType type);	//回退按钮
	void SitDown1(Ref* pSender, Widget::TouchEventType type);	//在一号位坐下
	void SitDown2(Ref* pSender, Widget::TouchEventType type);	//在二号位坐下
public:
	void UpdateReadyHome();	//新玩家进入是刷新Ui
};

#endif // __READYHOME_SCENE_H__
