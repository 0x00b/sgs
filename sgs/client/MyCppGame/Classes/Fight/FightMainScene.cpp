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
	
	//���½��ҷ��佫s
	img_my_hero = ImageView::create("Fight/hero_big/liubei.png");
	img_my_hero->setAnchorPoint(Vec2(1, 0));
	img_my_hero->setPosition(Vec2(img_bg->getContentSize().width, 0));
	img_bg->addChild(img_my_hero);

	img_my_hero_country = ImageView::create("Fight/SHUZI.png");
	img_my_hero_country->setAnchorPoint(Vec2(0, 1));
	img_my_hero_country->setPosition(Vec2(0, img_my_hero->getContentSize().height));
	//img_my_hero_country->setScale(visibleSize.width / 8 / img_my_hero->getContentSize().width);	//�ӿؼ��游�ؼ�����
	img_my_hero->addChild(img_my_hero_country);

	lab_my_hero_name = Label::createWithTTF(CSGSTXT::GET("liubei"), "fonts/FZBWKSK.TTF", 36);
	lab_my_hero_name->setTextColor(ccc4(0, 0, 0, 255));
	lab_my_hero_name->setAnchorPoint(Vec2(0, 1));
	lab_my_hero_name->setPosition(Vec2(0, img_my_hero->getContentSize().height - img_my_hero_country->getContentSize().height));
	img_my_hero->addChild(lab_my_hero_name);

	img_my_hero->setScale(visibleSize.width / 8 / img_my_hero->getContentSize().width);	//�佫��Ϣ���ŵ����1/8
	//���½��ҷ��佫e

	//���Ϸ��з��佫s
	img_enemy_hero = ImageView::create("Fight/hero_big/sunshangxiang.png");
	img_enemy_hero->setAnchorPoint(Vec2(0.5, 1));
	img_enemy_hero->setPosition(Vec2(img_bg->getContentSize().width / 2, img_bg->getContentSize().height));
	img_bg->addChild(img_enemy_hero);

	img_enemy_hero_country = ImageView::create("Fight/WUZI.png");
	img_enemy_hero_country->setAnchorPoint(Vec2(0, 1));
	img_enemy_hero_country->setPosition(Vec2(0, img_enemy_hero->getContentSize().height));
	img_enemy_hero->addChild(img_enemy_hero_country);

	lab_enemy_hero_name = Label::createWithTTF(CSGSTXT::GET("sunshangxiang"), "fonts/FZBWKSK.TTF", 36);
	lab_enemy_hero_name->setTextColor(ccc4(0, 0, 0, 255));
	lab_enemy_hero_name->setAnchorPoint(Vec2(0, 1));
	lab_enemy_hero_name->setPosition(Vec2(0, img_enemy_hero->getContentSize().height - img_enemy_hero_country->getContentSize().height));
	img_enemy_hero->addChild(lab_enemy_hero_name);

	img_enemy_hero->setScale(visibleSize.width / 8 / img_enemy_hero->getContentSize().width);	//�佫��Ϣ���ŵ����1/8
	//���Ϸ��з��佫e

	selectHero = SelectHero2Layer::create();
	this->addChild(selectHero);

	return true;
}

void FightMain::UpdateHeroInfo() {
	//���õ����佫��Ϣ
	img_my_hero->loadTexture("Fight/hero_big/liubei.png");
	img_my_hero_country->loadTexture("Fight/SHUZI.png");
	lab_hero_name->setString(CSGSTXT::GET("liubei"));
}