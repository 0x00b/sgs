#include "SelectHero2Layer.h"



SelectHero2Layer::SelectHero2Layer()
{
}


SelectHero2Layer::~SelectHero2Layer()
{
}

bool SelectHero2Layer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	cocos2d::ui::Button*  button_all_hero[10];
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *backGround = Sprite::create("res/model_select_bg.png");
	backGround->setPosition(0, 0);
	backGround->setAnchorPoint(Point(0, 0));
	Size mywinsize = Director::getInstance()->getWinSize(); 
	win = mywinsize;
	float winw = mywinsize.width; //获取屏幕宽度
	float winh = mywinsize.height;//获取屏幕高度
	float spx = backGround->getContentSize().width;
	float spy = backGround->getContentSize().height;
	backGround->setScaleX(winw / spx); //设置精灵宽度缩放比例
	backGround->setScaleY(winh / spy);
	this->addChild(backGround);

	setProgressTime(&progresstime1);   //初始化CCProgressTimer
	this->addChild(progresstime1);

	this->scheduleUpdate();        //调用定时器更新进度条

	return true;
}

void SelectHero2Layer::setProgressTime(CCProgressTimer **progresstime1)
{
	CCSprite *psSprite1 = CCSprite::create("res/progress_timebar.png");  //利用精灵创建进度条，并设置一些属性
	*progresstime1 = CCProgressTimer::create(psSprite1);

	float spx = psSprite1->getContentSize().width;
	float spy = psSprite1->getContentSize().height;
	float scale_x, scale_y;
	scale_x = win.width*0.40 / spx;
	scale_y = win.height*0.05 / spy;
	(*progresstime1)->setPercentage(100.0f);    //设置初始百分比的值
//	(*progresstime1)->setScale(3);            //设置进度条大小为原始的3倍
	(*progresstime1)->setScaleX(scale_x);
	(*progresstime1)->setScaleY(scale_y);
	//设置倍数

	(*progresstime1)->setMidpoint(ccp(0, 0.5));
	(*progresstime1)->setBarChangeRate(ccp(1, 0));
	(*progresstime1)->setType(kCCProgressTimerTypeBar);    //设置进度条为水平  //0.12  0.43
	(*progresstime1)->setAnchorPoint(Point(0, 0));
	(*progresstime1)->setPosition(win.width*0.28, win.height*0.08);    	//设置位置
//	this->addChild(progresstime1, 100);    //加入Layer中
}

void SelectHero2Layer::update(float dt)
{
	//CCProgressTimer *progresstime = static_cast(this->getChildByTag(100));
	float ct1 = progresstime1->getPercentage();    //取得当前进度的百分比

	ct1 = ct1 - 0.5f;    //每帧-0.5%

	//如果进度条小于100%，设置进度条的百分比
	if (ct1 >= 10)
	{
	//	CCLOG("progresstime1:%f, progresstime2:%f", ct1, ct2);
		progresstime1->setPercentage(ct1);
	}
	//如果进度条达到100%，则进入过渡场景，过渡场景会在2秒后进入主场景
	else
	{
	//	CCTransitionFade *tScene = CCTransitionFade::create(2, HelloWorld::scene(), ccWHITE);
	//	CCDirector::sharedDirector()->replaceScene(tScene);
	}

}

void SelectHero2Layer::ShowHero(int hero[10])
{

	int i, j;

	char name_pic[50]="SelectHero2/";
	char name2_pic[50];

	for (i = 0; i < 10; i++)
	{
		sprintf(name_pic, "SelectHero2/%d.png",hero[i]);  //   \\转义
		sprintf(name2_pic, "SelectHero2/%d.png", hero[i]);
		button_hero[i] = cocos2d::ui::Button::create(name_pic, name2_pic, name_pic);
		size_hero[i] = button_hero[i]->getCustomSize();
	}

	for (i = 0; i < 10; i++)
	{
		scale_x[i] = win.width / 6 / size_hero[i].width;
		scale_y[i] = win.width * 0.4 / size_hero[i].height;
		button_hero[i]->setScaleX(scale_x[i]);
		button_hero[i]->setScaleY(scale_y[i]);
		button_hero[i]->setAnchorPoint(Point(0, 0));
	}
	
	for (i = 0; i < 5; i++)
	{
		position[i].x = win.width/12+i*(win.width*13/(60));
		position[i].y = win.height*0.5;
		button_hero[i]->setPosition(position[i]);
	}

	for (i = 5; i < 10; i++)
	{
		position[i].x = win.width / 12 + (i-5)*(win.width * 13 / (60));;
		position[i].y = win.height*0.15;
		button_hero[i]->setPosition(position[i]);
	}

	for (i = 0; i < 10; i++)
	{
		this->addChild(button_hero[i]);
	}
	
}