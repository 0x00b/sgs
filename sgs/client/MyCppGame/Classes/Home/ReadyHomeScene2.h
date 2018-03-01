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
	Button* btn_back;	//���˰�ť
	//ImageView* img_table_bg1;	//һ��λ���
	//ImageView* img_table_bg2;	//����λ���
	ImageView* img_table_bg[8];	//���λ
	Button* btn_ready;	//׼����ť

private:
	void DidBack(Ref* pSender, Widget::TouchEventType type);	//���˰�ť
	void SitDown1(Ref* pSender, Widget::TouchEventType type);	//��һ��λ����
	void SitDown2(Ref* pSender, Widget::TouchEventType type);	//�ڶ���λ����
public:
	void UpdateReadyHome();	//����ҽ�����ˢ��Ui
};

#endif // __READYHOME_SCENE_H__
