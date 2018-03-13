#include "FightEndLoseLayer.h"
#include "Home/ReadyHomeScene2.h"

USING_NS_CC;
using namespace ui;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SearchHomeLayer.cpp\n");
}

// on "init" you need to initialize your instance
bool FightEndLose::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...

	//添加背景s
	img_bg = ImageView::create("Fight/game_settlement_lost.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(img_bg);
	//添加背景e

	//胜利标识s
	ImageView* img_win = ImageView::create("Fight/settlement_lost.png");
	img_win->setPosition(Vec2(img_bg->getContentSize().width / 2, img_bg->getContentSize().height / 2));
	img_bg->addChild(img_win);
	//胜利标识e

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/gameResult_lose.mp3", false);

	//初始化动画s
	img_bg->setScale(0);

	img_bg->runAction(ScaleTo::create(0.3, 1));
	//初始化动画e

	this->schedule(schedule_selector(FightEndLose::BackToHome), 0.0f, 0, 5.0f);	//5秒后跳转到房间界面

	return true;
}

void FightEndLose::BackToHome(float ft) {
	u_room.m_nStatus = 1;
	u_player.MyCurrentScene = ReadyHome::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, u_player.MyCurrentScene));
}
