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
	//������s
	Layer* layer_bg = Layer::create();
	this->addChild(layer_bg);
	//������e

	//����ͼs
	ImageView* img_bg = ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer_bg->addChild(img_bg);
	//����ͼe

	//����
	ImageView* img_my_hero = ImageView::create("Fight/liubei_big.png");
	img_my_hero->setAnchorPoint(Vec2(1,0));
	img_my_hero->setPosition(Vec2(img_bg->getContentSize().width, 0));
	img_bg->addChild(img_my_hero);

	ImageView* img_my_hero_country = ImageView::create("Fight/SHUZI.png");
	img_my_hero_country->setAnchorPoint(Vec2(0, 1));
	img_my_hero_country->setPosition(Vec2(0, img_bg->getContentSize().height));
	img_my_hero->addChild(img_my_hero_country);

	return true;
}