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
	//boolean	onTouchModeBegan(Touch* touch, Event* event);	//选择模式时的拖拽事件
	//void onTouchModeMoved(Touch* touch, Event* event);
	//boolean	onTouchModeEnded(Touch* touch, Event* event);

	void AutoSlide(Ref* pSender, Widget::TouchEventType type);	//将选中模式自动滑动到屏幕中央 并且放大高亮

	void change6ImageBig(Node* sender);	//6人模式图片从小变大
	void change6ImageSmall(Node* sender);	//6人模式图片从大变小
	void change2ImageBig(Node* sender);	//2人模式图片从小变大
	void change2ImageSmall(Node* sender);	//2人模式图片从大变小

	void CreateHomePop(Ref* pSender, Widget::TouchEventType type);	//创建房间
	void DidFastEnter(Ref* pSender, Widget::TouchEventType type);	//快速加入
	void SearchHomePop(Ref* pSender, Widget::TouchEventType type);	//搜索房间弹出层

private:
	ui::ImageView* img_two;	//双人模式按钮
	ui::ImageView* img_six; //六人模式按钮
	ui::ImageView* lab_slct_bg;		//当前高亮的模式标签背景
	ui::ImageView* img_createhome;	//创建房间
	ui::ImageView* img_fastenter; //快速加入
	ui::ImageView* img_serchhome;	//搜索房间
	ui::ImageView* img_back;	//回退按钮
};

#endif // __SELECTMODE_SCENE_H__