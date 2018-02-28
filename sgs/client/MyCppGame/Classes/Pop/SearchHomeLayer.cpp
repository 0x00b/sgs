#include "SearchHomeLayer.h"

USING_NS_CC;
using namespace ui;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SearchHomeLayer.cpp\n");
}

// on "init" you need to initialize your instance
bool SearchHome::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	this->setColor(ccc3(128,128,128));
	log("%f %f", this->getContentSize().width, this->getContentSize().height);
	log("%f %f", this->getPosition().x, this->getPosition().y);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...

	//添加背景s
	img_bg = ImageView::create("Mode/home_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(img_bg);
	//添加背景e

	//中文显示s
	ValueMap message = FileUtils::getInstance()->getValueMapFromFile("fonts/ChineseStrings.xml");
	auto searchhomeString = message["searchhome"].asString();
	//中文显示e

	//标题s
	auto lab_searchhome = Label::createWithTTF(searchhomeString, "fonts/FZBWKSK.TTF", 22);
	Size size_bg = img_bg->getContentSize();
	lab_searchhome->setPosition(Vec2(size_bg.width / 2, size_bg.height));
	img_bg->addChild(lab_searchhome);
	//标题e

	//确定搜索按钮s
	btn_startsearch = Button::create("Bg/btn_bg.png");
	btn_startsearch->setPosition(Vec2(size_bg.width / 2, size_bg.height / 5));
	img_bg->addChild(btn_startsearch);

	auto lab_startsearch = Label::createWithTTF(message["startsearch"].asString(), "fonts/FZBWKSK.TTF", 22);
	lab_startsearch->setPosition(Vec2(size_bg.width / 2, size_bg.height / 5));
	img_bg->addChild(lab_startsearch);
	//确定搜索按钮e

	//初始化动画s
	img_bg->setScale(0);
	img_bg->runAction(ScaleTo::create(0.5, 1));
	//初始化动画e

	this->setSwallowsTouches(true);

	auto listener_closepop = EventListenerTouchOneByOne::create();
	listener_closepop->onTouchBegan = [&](Touch *t, Event *event)
	{
		log("listener_closepop Began");

		return true;
	};
	listener_closepop->onTouchEnded = [&](Touch *t, Event *event)
	{
		log("listener_closepop Ended");
		auto seq = Sequence::create(ScaleTo::create(0.5, 0), CallFuncN::create(CC_CALLBACK_1(SearchHome::closeAnimation, this)), NULL);
		img_bg->runAction(seq);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_closepop, this);

	return true;
}

void SearchHome::closeAnimation(Node* pSender) {
	this->removeFromParentAndCleanup(true);//true表示清空 回收内存
}
