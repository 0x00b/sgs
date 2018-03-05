#pragma once

#include "model/include_all.h"

USING_NS_CC;

using namespace std;

class SelectHero2Layer :public Layer
{
public:
	int pvp_hero[10];

	SelectHero2Layer();
	~SelectHero2Layer();

	virtual bool init();

	void update(float dt);

	void setProgressTime(CCProgressTimer **progresstime1);

	void ShowHero(int hero[10]);

	CREATE_FUNC(SelectHero2Layer);

	void select_hero_0(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_1(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_2(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_3(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_4(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_5(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_6(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_7(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_8(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void select_hero_9(Ref* sender, cocos2d::ui::Widget::TouchEventType type);


private:
	Size win;

	cocos2d::CCProgressTimer *progresstime1;

	cocos2d::ui::Button*  button_hero[10];  //10个武将

	Point position[10]; //10个武将位置
	Size size_hero[10];  //10个图大小
	float scale_x[10];  //10个图X倍数
	float scale_y[10];  //10个图Y倍数
	

};

