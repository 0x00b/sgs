#ifndef __SELECTMODE_SCENE_H__
#define __SELECTMODE_SCENE_H__

#include "SimpleAudioEngine.h"
#include "Pop/SearchHomeLayer.h"
#include "Home/ReadyHomeScene2.h"
#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "../Classes/model/include_all.h"

USING_NS_CC;
using namespace ui;

extern std::list<std::shared_ptr<PPacket>> g_lstWrite;

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
	ImageView* img_two;	//˫��ģʽ��ť
	ImageView* img_six; //����ģʽ��ť

	Button* btn_createhome;	//��������
	Button* btn_fastenter; //���ټ���
	Button* btn_searchhome;	//��������

	Button* btn_back;	//���˰�ť

	ImageView* lab_slct_bg;		//��ǰ������ģʽ��ǩ����
	Label* lab_slct_mode;	//��ǰѡ��ģʽ�ı�ǩ
};

#endif // __SELECTMODE_SCENE_H__