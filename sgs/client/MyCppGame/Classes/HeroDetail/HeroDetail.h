#pragma once

#include "../Classes/model/include_all.h"

USING_NS_CC;

using namespace std;

class HeroDetail : public cocos2d::Scene
{
public:
	HeroDetail();
	~HeroDetail();

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback

	// implement the "static create()" method manually
	CREATE_FUNC(HeroDetail);
public:
	//4个layer  分别放成蜀魏吴群的武将
	int i_check;
	vector<Hero>hero_detail;
	vector<cocos2d::ui::Button*>all_hero;
	vector<Sprite *>wei;
	vector<Sprite *>shu;
	vector<Sprite *>yu;
	vector<Sprite *>qun;
	Size win;
	Layer * country[4];
	Size country_size[4];
	float country_scale_x[4];
	float country_scale_y[4];
	Point position[4];
	cocos2d::ui::Button*  button_select_country[4];  
	int num_country[4];  //每个国家的英雄人数 
	cocos2d::ui::Button* btn_back;	//回退按钮
	Sprite *pic; //用来显示武将的精灵
	Label *skill[6]; //4个label 显示技能
public:
	void select_country_btn();
	void init_detail();
	void init_country_layer();
	void select_country(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void Selet_Detail_Hero(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void DidBack(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);	//回退按钮
};

