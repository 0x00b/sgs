#ifndef __FIGHTMAIN_SCENE_H__
#define __FIGHTMAIN_SCENE_H__

#include "model/include_all.h"
#include "SelectHero2Layer\SelectHero2Layer.h"

USING_NS_CC;
using namespace ui;

class FightMain : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FightMain);

public:
	SelectHero2Layer *selectHero;	//ѡ���佫��ָ��
private:
	ImageView* img_my_hero;				//�ҷ��佫��Ϣ
	ImageView* img_my_hero_country;
	Label* lab_my_hero_name;
	ImageView* img_enemy_hero;				//�Է��佫��Ϣ
	ImageView* img_enemy_hero_country;
	Label* lab_enemy_hero_name;
public:
	void UpdateHeroInfo();
};

#endif // __FIGHTMAIN_SCENE_H__
