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
	auto searchhomeString = CSGSTXT::GET("searchhome");
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
	btn_startsearch->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			Json::Value root;
			root[SRoom[ERoom_room_id]] = atoi(txt_homeid->getString().c_str());	//传房间号
			std::shared_ptr<PPacket> p(new PPacket());
			p->body = root.toStyledString();
			p->pack(PLAYER_ENTER_ROOM);
			g_lstWrite.push_back(p);
			break;
		}
		
	});

	auto lab_startsearch = Label::createWithTTF(CSGSTXT::GET("startsearch"), "fonts/FZBWKSK.TTF", 22);
	lab_startsearch->setPosition(Vec2(size_bg.width / 2, size_bg.height / 5));
	img_bg->addChild(lab_startsearch);
	//确定搜索按钮e

	//房间号s
	Label* lab_homeid = Label::create(CSGSTXT::GET("homeid"), "fonts/FZBWKSK.TTF", 22);
	lab_homeid->setPosition(Vec2(img_bg->getContentSize().width / 5, img_bg->getContentSize().height * 3 / 5));
	img_bg->addChild(lab_homeid);

	ImageView* img_homeid_bg = ImageView::create("Bg/txt_bg.png");
	img_homeid_bg->setPosition(Vec2(lab_homeid->getPosition().x + 70, img_bg->getContentSize().height * 3 / 5));
	img_homeid_bg->setAnchorPoint(Vec2(0, 0.5));
	img_bg->addChild(img_homeid_bg);

	txt_homeid = TextField::create();
	txt_homeid->setPlaceHolder("input homeid");
	txt_homeid->setPosition(Vec2(lab_homeid->getPosition().x + 75, img_bg->getContentSize().height * 3 / 5));
	txt_homeid->setAnchorPoint(Vec2(0, 0.5));
	img_bg->addChild(txt_homeid);
	//房间号e

	//初始化动画s
	img_bg->setScale(0);

	img_bg->runAction(ScaleTo::create(0.3, 1));
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
		auto seq = Sequence::create(ScaleTo::create(0.3, 0), CallFuncN::create(CC_CALLBACK_1(SearchHome::closeAnimation, this)), NULL);
		img_bg->runAction(seq);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_closepop, this);

	return true;
}

void SearchHome::closeAnimation(Node* pSender) {
	this->removeFromParentAndCleanup(true);//true表示清空 回收内存
}
