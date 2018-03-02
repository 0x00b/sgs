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
	float winw = mywinsize.width; //��ȡ��Ļ���
	float winh = mywinsize.height;//��ȡ��Ļ�߶�
	float spx = backGround->getContentSize().width;
	float spy = backGround->getContentSize().height;
	backGround->setScaleX(winw / spx); //���þ��������ű���
	backGround->setScaleY(winh / spy);
	this->addChild(backGround);

	setProgressTime(&progresstime1);   //��ʼ��CCProgressTimer
	this->addChild(progresstime1);

	this->scheduleUpdate();        //���ö�ʱ�����½�����

	return true;
}

void SelectHero2Layer::setProgressTime(CCProgressTimer **progresstime1)
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

void SelectHero2Layer::ShowHero(int hero[10])
{

	int i, j;

	char name_pic[50]="SelectHero2/";
	char name2_pic[50];

	for (i = 0; i < 10; i++)
	{
		sprintf(name_pic, "SelectHero2/%d.png",hero[i]);  //   \\ת��
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