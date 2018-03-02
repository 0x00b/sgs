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
	~ReadyHome();

	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(ReadyHome);

private:
	Button* btn_back;	//回退按钮
	ImageView* img_table_bg[8];	//玩家位
	Label* lab_table_name[8];	//玩家名 用账号代做标志
	Button* btn_ready;	//准备按钮
	Label* lab_homeid;	//房间号
private:
	void DidBack(Ref* pSender, Widget::TouchEventType type);	//回退按钮
public:
	void UpdateReadyHome();	//新玩家进入时刷新Ui
};

#endif // __READYHOME_SCENE_H__
