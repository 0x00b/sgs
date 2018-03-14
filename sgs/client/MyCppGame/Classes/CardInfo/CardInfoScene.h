#ifndef __CARDINFO_SCENE_H__
#define __CARDINFO_SCENE_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "text.h"

USING_NS_CC;
using namespace ui;

class CardInfo : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(CardInfo);
private:
	ImageView* img_map;
	Button* btn_cards[30];
	Button* btn_back;	//回退按钮

	Label* lab_card_detail;

	float old_y;
	bool flag;
private:
	bool onTouchMapBegan(Touch* touch, Event* event);
	void onTouchMapMoved(Touch* touch, Event* event);
	bool onTouchMapEnded(Touch* touch, Event* event);

	void DidBack(Ref* pSender, Widget::TouchEventType type);	//回退按钮
};

#endif // __CARDINFO_SCENE_H__