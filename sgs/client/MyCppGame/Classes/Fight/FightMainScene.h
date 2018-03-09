#ifndef __FIGHTMAIN_SCENE_H__
#define __FIGHTMAIN_SCENE_H__

#include "model/include_all.h"
#include "SelectHero2Layer\SelectHero2Layer.h"
#include "./model/sgscard.h"
#include "Fight/FightEndLoseLayer.h"
#include "Fight/FightEndWinLayer.h"

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
	Size win;
	TextField* txt_chat;	//����

	Label* chat[8];

	Sprite *chat_bg; //���챳��
	Vector<SpriteFrame*> sha_vec;
	Vector<SpriteFrame*> shan_vec;
	Vector<SpriteFrame*> tao_vec;
	Sprite *animation_sha;
	Sprite *animation_shan;
	Sprite *animation_tao;
	ImageView* img_bg;	//����ͼ
	ImageView* img_hero[2];				//�佫��Ϣ
	ImageView* img_hero_info_bg[2];	//�������佫���Һ������ı���ɫ
	ImageView* img_hero_country[2];
	Label* lab_hero_name[2];
	ImageView* img_handcard_num_bg[2];	//����������
	Label* lab_handcard_num[2];	//������
	ImageView* img_blood[2][4];	//Ѫ ����ĸ� �ڳ�ʼ���佫��Ϣ��ʱ���ʼ��

	//ImageView* img_enemy_hero;				//�Է��佫��Ϣ
	//ImageView* img_enemy_hero_info_bg;	//�������佫���Һ������ı���ɫ
	//ImageView* img_enemy_hero_country;
	//Label* lab_enemy_hero_name;
	//ImageView* img_enemy_handcard_num_bg;	//�з�����������
	//Label* lab_enemy_handcard_num;	//�з�������

	ProgressTimer* pt_0;	//�ҷ����ֶ�ʱ
	ProgressTimer* pt_1;	//�з����ֶ�ʱ

	int stage;	//��ǰ���ڵĽ׶� ���� ���� 0����ʼ�� 1������ 2������ 3�����ֻغ� �ȴ�
	int status;				//��ǰ���Ե��������
	Sprite* sp_handcard[20];	//����
	int i_current_card_num;	//��ǰ������
	ImageView* img_handcard_num[20];	//����
	ImageView* img_handcard_flowercolor[20];	//��ɫ
	int i_current_card[20];	//��ǰѡ�е����Ʊ��

	Button* btn_confirm;  //ȷ��
	Button* btn_cancel;  //ȡ��

	Label* lab_now_stage;	//��ʾ��ǰ�׶εı�ǩ
public:
	void InitHeroInfo();				//��ʼ�������佫��Ϣ
	void Vec_create();
	bool onTouchHandCardBegan(Touch* touch, Event* event);		//���ƵĴ����¼�
	void onTouchHandCardMoved(Touch* touch, Event* event);
	bool onTouchHandCardEnded(Touch* touch, Event* event);
	void btn_confirm_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type);	//����ȷ���¼�
	void btn_cancel_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type);	//����ȡ���¼�
	void UpdateHandCard();			//��������
	void UpdateFightInfo(int i,int blood,int max_blood);			//���� ��ս��Ϣ Ѫ�� ��һ������0������ 1������� �ڶ�����������Ѫ�� �������������Ѫ��
	void ShowMyBtnAndTimer();		//��ʾ�ҵİ�ť�Ͷ�ʱ��
	void HideMyBtnAndTimer();		//�����ҵİ�ť�Ͷ�ʱ��
	void ShowEnemyTimer();			//��ʾ���ֶ�ʱ��
	void HideEnemyTimer();			//���ض��ֶ�ʱ��

	void hid_sha(Node* sender);   //��ɱ�ľ�������
	void hid_shan(Node* sender);  //�����ľ�������
	void hid_tao(Node* sender);  //���ҵľ�������
	void show_sha(int i);  //��ʾɱ
	void show_shan(int i); //��ʾ��
	void show_tao(int i);  //��ʾ��
	void UpdateChat();  //�����������

	void setStatus(int i);
	int getStatus();
	void setStage(int i);

	void textFieldEvent(Ref * pSender, TextField::EventType type);  //textfield�Ļص�����
	void UpdateHandCardNum(int i,int cnt);		//���������� ��һ������0������ 1������� �ڶ�������������������
	void UpdateStageLab(std::string stage_name);	//���µ�ǰ�׶�
	void GameEnd(int i);		//��Ϸ����	0����ʤ�� 1����ʧ��
};

#endif // __FIGHTMAIN_SCENE_H__
