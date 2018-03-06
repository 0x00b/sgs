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
	SelectHero2Layer *selectHero;	//ѡ���佫��ָ��
private:
	ImageView* img_bg;	//����ͼ

	ImageView* img_hero[2];				//�ҷ��佫��Ϣ
	ImageView* img_hero_info_bg[2];	//�������佫���Һ������ı���ɫ
	ImageView* img_hero_country[2];
	Label* lab_hero_name[2];
	ImageView* img_handcard_num_bg[2];	//�ҷ�����������
	Label* lab_handcard_num[2];	//�ҷ�������

	ImageView* img_enemy_hero;				//�Է��佫��Ϣ
	ImageView* img_enemy_hero_info_bg;	//�������佫���Һ������ı���ɫ
	ImageView* img_enemy_hero_country;
	Label* lab_enemy_hero_name;
	ImageView* img_enemy_handcard_num_bg;	//�з�����������
	Label* lab_enemy_handcard_num;	//�з�������

	ProgressTimer* pt_0;	//�ҷ����ֶ�ʱ
	ProgressTimer* pt_1;	//�з����ֶ�ʱ

	Sprite* sp_handcard[20];	//��ǰ����
	ImageView* img_handcard_num[20];	//����
	ImageView* img_handcard_flowercolor[20];	//��ɫ
	int i_current_card = -1;	//��ǰѡ�е����Ʊ��
public:
	void InitHeroInfo();				//��ʼ�������佫��Ϣ

	bool onTouchHandCardBegan(Touch* touch, Event* event);		//���ƵĴ����¼�
	void onTouchHandCardMoved(Touch* touch, Event* event);
	bool onTouchHandCardEnded(Touch* touch, Event* event);

	void UpdateHandCard();
};

#endif // __FIGHTMAIN_SCENE_H__
