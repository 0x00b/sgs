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
	float winw = mywinsize.width; //��ȡ��Ļ���
	float winh = mywinsize.height;//��ȡ��Ļ�߶�
	float spx = backGround->getContentSize().width;
	float spy = backGround->getContentSize().height;
	backGround->setScaleX(winw / spx); //���þ��������ű���
	backGround->setScaleY(winh / spy);
	this->addChild(backGround);

	setProgressTime(&progresstime1,mywinsize);   //��ʼ��CCProgressTimer
	this->addChild(progresstime1);

	this->scheduleUpdate();        //���ö�ʱ�����½�����

	return true;
}

void SelectHero2Layer::setProgressTime(CCProgressTimer **progresstime1,Size win)
{
	CCSprite *psSprite1 = CCSprite::create("res/progress_timebar.png");  //���þ��鴴����������������һЩ����
	*progresstime1 = CCProgressTimer::create(psSprite1);

	float spx = psSprite1->getContentSize().width;
	float spy = psSprite1->getContentSize().height;
	float scale_x, scale_y;
	scale_x = win.width*0.40 / spx;
	scale_y = win.height*0.05 / spy;
	(*progresstime1)->setPercentage(100.0f);    //���ó�ʼ�ٷֱȵ�ֵ
//	(*progresstime1)->setScale(3);            //���ý�������СΪԭʼ��3��
	(*progresstime1)->setScaleX(scale_x);
	(*progresstime1)->setScaleY(scale_y);
	//���ñ���

	(*progresstime1)->setMidpoint(ccp(0, 0.5));
	(*progresstime1)->setBarChangeRate(ccp(1, 0));
	(*progresstime1)->setType(kCCProgressTimerTypeBar);    //���ý�����Ϊˮƽ  //0.12  0.43
	(*progresstime1)->setAnchorPoint(Point(0, 0));
	(*progresstime1)->setPosition(win.width*0.28, win.height*0.08);    	//����λ��
//	this->addChild(progresstime1, 100);    //����Layer��
}

void SelectHero2Layer::update(float dt)
{
	//CCProgressTimer *progresstime = static_cast(this->getChildByTag(100));
	float ct1 = progresstime1->getPercentage();    //ȡ�õ�ǰ���ȵİٷֱ�

	ct1 = ct1 - 0.5f;    //ÿ֡-0.5%

	//���������С��100%�����ý������İٷֱ�
	if (ct1 >= 10)
	{
	//	CCLOG("progresstime1:%f, progresstime2:%f", ct1, ct2);
		progresstime1->setPercentage(ct1);
	}
	//����������ﵽ100%���������ɳ��������ɳ�������2������������
	else
	{
	//	CCTransitionFade *tScene = CCTransitionFade::create(2, HelloWorld::scene(), ccWHITE);
	//	CCDirector::sharedDirector()->replaceScene(tScene);
	}

}