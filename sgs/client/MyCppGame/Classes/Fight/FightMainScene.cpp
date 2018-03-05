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
	
	//ÓÒÏÂ½ÇÎä½«s
	ImageView* img_my_hero = ImageView::create("Fight/hero_big/liubei.png");
	img_my_hero->setAnchorPoint(Vec2(1, 0));
	img_my_hero->setPosition(Vec2(img_bg->getContentSize().width, 0));

	img_bg->addChild(img_my_hero);

	ImageView* img_my_hero_country = ImageView::create("Fight/SHUZI.png");
	img_my_hero_country->setAnchorPoint(Vec2(0, 1));
	img_my_hero_country->setPosition(Vec2(0, img_my_hero->getContentSize().height));
	//img_my_hero_country->setScale(visibleSize.width / 8 / img_my_hero->getContentSize().width);	//×Ó¿Ø¼þËæ¸¸¿Ø¼þËõ·Å
	img_my_hero->addChild(img_my_hero_country);

	Label* lab_hero_name = Label::createWithTTF(CSGSTXT::GET("liubei"), "fonts/FZBWKSK.TTF", 36);
	lab_hero_name->setTextColor(ccc4(0, 0, 0, 255));
	lab_hero_name->setAnchorPoint(Vec2(0, 1));
	lab_hero_name->setPosition(Vec2(0, img_my_hero->getContentSize().height - img_my_hero_country->getContentSize().height));
	img_my_hero->addChild(lab_hero_name);

	img_my_hero->setScale(visibleSize.width / 8 / img_my_hero->getContentSize().width);	//Îä½«ÐÅÏ¢Ëõ·Åµ½¿í¶È1/8
	//ÓÒÏÂ½ÇÎä½«e

	selectHero = SelectHero2Layer::create();
	this->addChild(selectHero,2,"selectHero");

	return true;
}