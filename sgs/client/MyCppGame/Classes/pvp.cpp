#include "pvp.h"

pvp::pvp()
{
}

pvp::~pvp()
{
}




Scene* pvp::createScene()
{

	Scene * main_scene = Scene::create();
	auto layer = pvp::create();
//	main_scene->addChild(layer, 0, 3);
	main_scene->addChild(layer);

	return main_scene;
}

bool pvp::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *bg_pic = Sprite::create("res/pvp/login_bg.png");
	bg_pic->setAnchorPoint(Point(0, 0));
	bg_pic->setPosition(0, 0);
	float spx = bg_pic->getContentSize().width;
	float spy = bg_pic->getContentSize().height;
	bg_pic->setScaleX(visibleSize.width / spx); //设置精灵宽度缩放比例
	bg_pic->setScaleY(visibleSize.height / spy);
	this->addChild(bg_pic);

	Sprite* zhuangbeikuang[4];
	int i;
	
	for (i = 0; i < 4; i++)
	{
		zhuangbeikuang[i] = Sprite::create("res/pvp/zhuangbeikuang.png");
		zhuangbeikuang[i]->setAnchorPoint(Point(0, 0));
	}

	float zhuangbeipai_scale_x = visibleSize.width / 9 / zhuangbeikuang[0]->getContentSize().width;
	float zhuangbeipai_scale_y = visibleSize.height / 15 / zhuangbeikuang[0]->getContentSize().height;

	for (i = 0; i < 4; i++)
	{
		zhuangbeikuang[i]->setScaleX(zhuangbeipai_scale_x);
		zhuangbeikuang[i]->setScaleY(zhuangbeipai_scale_y);
		zhuangbeikuang[i]->setPosition(visibleSize.width / 20, i*visibleSize.height / 15);
		addChild(zhuangbeikuang[i]);
	}

	Sprite * player = Sprite::create("res/pvp/1.png");
	player->setAnchorPoint(Point(0,0));
	player->setPosition(visibleSize.width*0.81,0);
	player->setScale(1.5);
	addChild(player);

	Sprite * blood[4];
	
	for (i = 0; i < 4; i++)
	{
		blood[i] = Sprite::create("res/pvp/blood_green.png");
		blood[i]->setAnchorPoint(Point(1, 0));
		blood[i]->setScale(0.4);
	}
	
	Size blood_size = blood[0]->getContentSize();

	for (i = 0; i < 4; i++)
	{
		blood[i]->setPosition(visibleSize.width, i*blood_size.height*0.53);
		addChild(blood[i]);
	}

	return true;
}
