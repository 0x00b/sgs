#ifndef __SELECTMODE_SCENE_H__
#define __SELECTMODE_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include "Pop/SearchHomeLayer.h"
#include "Home/ReadyHomeScene2.h"

USING_NS_CC;
using namespace ui;

class SelectMode : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(SelectMode);

private:
	//boolean	onTouchModeBegan(Touch* touch, Event* event);	//ѡ��ģʽʱ����ק�¼�
	//void onTouchModeMoved(Touch* touch, Event* event);
	//boolean	onTouchModeEnded(Touch* touch, Event* event);

	void AutoSlide(Ref* pSender, Widget::TouchEventType type);	//��ѡ��ģʽ�Զ���������Ļ���� ���ҷŴ����

	void change6ImageBig(Node* sender);	//6��ģʽͼƬ��С���
	void change6ImageSmall(Node* sender);	//6��ģʽͼƬ�Ӵ��С
	void change2ImageBig(Node* sender);	//2��ģʽͼƬ��С���
	void change2ImageSmall(Node* sender);	//2��ģʽͼƬ�Ӵ��С

	void CreateHomePop(Ref* pSender, Widget::TouchEventType type);	//��������
	void DidFastEnter(Ref* pSender, Widget::TouchEventType type);	//���ټ���
	void SearchHomePop(Ref* pSender, Widget::TouchEventType type);	//�������䵯����

private:
	ui::ImageView* img_two;	//˫��ģʽ��ť
	ui::ImageView* img_six; //����ģʽ��ť
	ui::ImageView* lab_slct_bg;		//��ǰ������ģʽ��ǩ����
	ui::ImageView* img_createhome;	//��������
	ui::ImageView* img_fastenter; //���ټ���
	ui::ImageView* img_serchhome;	//��������
	ui::ImageView* img_back;	//���˰�ť
};

#endif // __SELECTMODE_SCENE_H__