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
	Button* btn_back;	//���˰�ť
	ImageView* img_table_bg[8];	//���λ
	Label* lab_table_name[8];	//����� ���˺Ŵ�����־
	Button* btn_ready;	//׼����ť
	Label* lab_homeid;	//�����
private:
	void DidBack(Ref* pSender, Widget::TouchEventType type);	//���˰�ť
public:
	void UpdateReadyHome();	//����ҽ���ʱˢ��Ui
};

#endif // __READYHOME_SCENE_H__
