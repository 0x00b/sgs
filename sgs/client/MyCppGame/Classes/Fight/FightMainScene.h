#ifndef __FIGHTMAIN_SCENE_H__
#define __FIGHTMAIN_SCENE_H__

#include "model/include_all.h"
#include "SelectHero2Layer\SelectHero2Layer.h"
#include "./model/sgscard.h"

USING_NS_CC;
using namespace ui;

class FightMain : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FightMain);

public:
	SelectHero2Layer *selectHero;	//选择武将层指针
private:
	ImageView* img_bg;	//背景图

	ImageView* img_hero[2];				//我方武将信息
	ImageView* img_hero_info_bg[2];	//用于在武将国家和姓名的背景色
	ImageView* img_hero_country[2];
	Label* lab_hero_name[2];
	ImageView* img_handcard_num_bg[2];	//我方手牌数背景
	Label* lab_handcard_num[2];	//我方手牌数
	ImageView* img_blood[2][4];	//血 最多五个 在初始化武将信息的时候初始化

	ImageView* img_enemy_hero;				//对方武将信息
	ImageView* img_enemy_hero_info_bg;	//用于在武将国家和姓名的背景色
	ImageView* img_enemy_hero_country;
	Label* lab_enemy_hero_name;
	ImageView* img_enemy_handcard_num_bg;	//敌方手牌数背景
	Label* lab_enemy_handcard_num;	//敌方手牌数

	ProgressTimer* pt_0;	//我方出手定时
	ProgressTimer* pt_1;	//敌方出手定时

	Sprite* sp_handcard[20];	//手牌
	int i_current_card_num;	//当前手牌数
	ImageView* img_handcard_num[20];	//点数
	ImageView* img_handcard_flowercolor[20];	//花色
	int i_current_card = -1;	//当前选中的手牌编号

	Button* btn_confirm;  //确定

public:
	void InitHeroInfo();				//初始化敌我武将信息

	bool onTouchHandCardBegan(Touch* touch, Event* event);		//手牌的触摸事件
	void onTouchHandCardMoved(Touch* touch, Event* event);
	bool onTouchHandCardEnded(Touch* touch, Event* event);
	void btn_confirm_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void UpdateHandCard();
};

#endif // __FIGHTMAIN_SCENE_H__
