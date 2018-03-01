#include "ReadyHomeScene2.h"

USING_NS_CC;
using namespace ui;

Scene* ReadyHome::createScene()
{
	return ReadyHome::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ReadyHomeScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ReadyHome::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...

	//��ӱ���s
	auto layer_bg = Layer::create();
	this->addChild(layer_bg);

	ImageView* img_bg = ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//����Ĵ���������ͼƬǡ�ó�����Ļ ������Ϊ�������ű�����ͬ ������ͼƬ����
	//img_bg->setScale(visibleSize.width/img_bg->getContentSize().width, visibleSize.height / img_bg->getContentSize().height);
	layer_bg->addChild(img_bg);
	//��ӱ���e

	//��ӻ��˰�ťs
	btn_back = Button::create("Bg/back_bg.png");
	btn_back->setAnchorPoint(Vec2(0, 1));
	btn_back->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	img_bg->addChild(btn_back);

	btn_back->addTouchEventListener(CC_CALLBACK_2(ReadyHome::DidBack, this));
	//��ӻ��˰�ťe

	//������λs
	img_table_bg1 = ui::ImageView::create("Home/generalface_mystery.png");
	img_table_bg1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 172, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_table_bg1);
	img_table_bg1->setTouchEnabled(true);
	img_table_bg1->addTouchEventListener(CC_CALLBACK_2(ReadyHome::SitDown1, this));

	img_table_bg2 = ui::ImageView::create("Home/generalface_mystery.png");
	img_table_bg2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 172, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_table_bg2);
	img_table_bg2->setTouchEnabled(true);
	img_table_bg2->addTouchEventListener(CC_CALLBACK_2(ReadyHome::SitDown2, this));
	//������λs

	//��ʼ��ťs
	btn_ready = Button::create("Home/chapter_normal.png", "Home/chapter_selected.png", "Home/disabled_image.png");
	btn_ready->setTitleText(SGSTXT["ready"]);
	btn_ready->setTitleFontName("fonts/FZBWKSK.TTF");
	btn_ready->setTitleFontSize(40);

	btn_ready->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	btn_ready->setPosition(Vec2(origin.x + visibleSize.width - 150, origin.y + visibleSize.height / 2));
	img_bg->addChild(btn_ready);
	//��ʼ��ťe
	
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
	{
		if ((*it).m_nSeatId == 0)
		{
			img_table_bg1->loadTexture("Home/generalface_soldier1.png");
		}
		else
		{
			img_table_bg2->loadTexture("Home/generalface_soldier1.png");
		}
	}

	return true;
}

void ReadyHome::DidBack(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto SelectModeScene = SelectMode::createScene();
		director->replaceScene(TransitionSlideInL::create(0.5f, SelectModeScene));
		break;
	}
}

void ReadyHome::SitDown1(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		img_table_bg1->loadTexture("Home/generalface_soldier1.png");
		img_table_bg2->loadTexture("Home/generalface_mystery.png");
		break;
	}
}

void ReadyHome::SitDown2(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		img_table_bg1->loadTexture("Home/generalface_mystery.png");
		img_table_bg2->loadTexture("Home/generalface_soldier1.png");
		break;
	}
}

void ReadyHome::UpdateReadyHome() {
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
	{
		if ((*it).m_nSeatId == 0)
		{
			img_table_bg1->loadTexture("Home/generalface_soldier1.png");
		}
		else
		{
			img_table_bg2->loadTexture("Home/generalface_soldier1.png");
		}
	}
}