#include "FightMainScene.h"

USING_NS_CC;
using namespace ui;

Scene* FightMain::createScene()
{
	return FightMain::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in FightMainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FightMain::init()
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
	//±³¾°²ãs
	Layer* layer_bg = Layer::create();
	this->addChild(layer_bg);
	//±³¾°²ãe

	//±³¾°Í¼s
	ImageView* img_bg = ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer_bg->addChild(img_bg);
	//±³¾°Í¼e

	//²âÊÔ
	ImageView* c = ImageView::create("Bg/txt_bg.png");
	c->setPosition(Vec2(img_bg->getContentSize().width / 2, img_bg->getContentSize().height / 2));
	img_bg->addChild(c);

	return true;
}