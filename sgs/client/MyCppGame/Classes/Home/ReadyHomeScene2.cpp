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

	//添加背景s
	auto layer_bg = Layer::create();
	this->addChild(layer_bg);

	ImageView* img_bg = ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//下面的代码让缩放图片恰好充满屏幕 但是因为长款缩放比例不同 可能让图片变形
	//img_bg->setScale(visibleSize.width/img_bg->getContentSize().width, visibleSize.height / img_bg->getContentSize().height);
	layer_bg->addChild(img_bg);
	//添加背景e

	//添加回退按钮s
	img_back = ImageView::create("Bg/back_bg.png");
	img_back->setAnchorPoint(Vec2(0, 1));
	img_back->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	img_bg->addChild(img_back);

	img_back->setTouchEnabled(true);
	img_back->addTouchEventListener(CC_CALLBACK_2(ReadyHome::DidBack, this));
	//添加回退按钮e

	//两个座位s
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
	//两个座位s

	//开始按钮s
	btn_start = Button::create("Home/chapter_normal.png", "Home/chapter_selected.png", "Home/disabled_image.png");
	btn_start->setTitleText("Start");

	btn_start->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	btn_start->setPosition(Vec2(origin.x + visibleSize.width - 150, origin.y + visibleSize.height / 2));
	img_bg->addChild(btn_start);
	//开始按钮e

	return true;
}

void ReadyHome::DidBack(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto SelectModeScene = SelectMode::createScene();
		director->replaceScene(TransitionSlideInL::create(1.0f, SelectModeScene));
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
