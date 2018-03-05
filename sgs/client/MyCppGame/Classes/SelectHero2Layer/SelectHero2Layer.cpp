#include "SelectHero2Layer.h"
#include "../Classes/model/hero.h"


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

	char name_pic[50];
	char name2_pic[50];

	for (i = 0; i < 10; i++)
	{
		pvp_hero[i] = hero[i];
		sprintf(name_pic, "SelectHero2/%d.png",hero[i]);  //   \\ת��
		sprintf(name2_pic, "SelectHero2/%d.png", hero[i]);
		button_hero[i] = cocos2d::ui::Button::create(name_pic, name2_pic, name_pic);
		size_hero[i] = button_hero[i]->getCustomSize();
	}

	for (i = 0; i < 10; i++)
	{
		scale_x[i] = win.width / 7 / size_hero[i].width;
		scale_y[i] = win.height * 0.35 / size_hero[i].height;
		button_hero[i]->setScaleX(scale_x[i]);
		button_hero[i]->setScaleY(scale_y[i]);
		button_hero[i]->setAnchorPoint(Point(0, 0));
	}
	
	for (i = 0; i < 5; i++)
	{
		position[i].x = win.width/16+i*(win.width/6);
		position[i].y = win.height*0.5;
		button_hero[i]->setPosition(position[i]);
	}

	for (i = 5; i < 10; i++)
	{
		position[i].x = win.width / 16 + (i-5)*(win.width /6);
		position[i].y = win.height*0.13;
		button_hero[i]->setPosition(position[i]);
	}

	button_hero[0]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_0, this));
	button_hero[1]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_1, this));
	button_hero[2]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_2, this));
	button_hero[3]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_3, this));
	button_hero[4]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_4, this));
	button_hero[5]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_5, this));
	button_hero[6]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_6, this));
	button_hero[7]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_7, this));
	button_hero[8]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_8, this));
	button_hero[9]->addTouchEventListener(CC_CALLBACK_2(SelectHero2Layer::select_hero_9, this));

	for (i = 0; i < 10; i++)
	{
		this->addChild(button_hero[i]);
	}
	
}

void SelectHero2Layer::select_hero_0(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{  //���this�������ť�ڵ���һlayer
		Json::Value root;
		root["idhero"] = 1;
		std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{ 
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 1;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_1(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 2;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 2;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_2(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 3;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 3;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_3(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 4;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 4;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_4(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 5;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 5;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_5(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 6;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 6;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_6(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 7;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 7;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_7(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 8;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 8;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_8(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 9;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 9;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

void SelectHero2Layer::select_hero_9(Ref* sender, cocos2d::ui::Widget::TouchEventType type)     //���this�������ť�ڵ���һlayer
{
	Json::Value root;
	root["idhero"] = 10;
	std::shared_ptr<PPacket> p(new PPacket());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		u_player.m_oGameAttr.m_pHero->idhero = 10;
		p->body = root.toStyledString();
		p->pack(GAME_SELECT_HERO);
		g_lstWrite.push_back(p);
//		this->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}