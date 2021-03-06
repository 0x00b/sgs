#include "SelectModeScene.h"

USING_NS_CC;
using namespace ui;

Scene* SelectMode::createScene()
{
	return SelectMode::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SelectMode::init()
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

	ui::ImageView* img_bg = ui::ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//下面的代码让缩放图片恰好充满屏幕 但是因为长款缩放比例不同 可能让图片变形
	//img_bg->setScale(visibleSize.width/img_bg->getContentSize().width, visibleSize.height / img_bg->getContentSize().height);
	layer_bg->addChild(img_bg);
	//添加背景e

	//添加选择模式背景图s
	ui::ImageView* img_slct_bg = ui::ImageView::create("Mode/model_select_bg.png");
	img_slct_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_slct_bg);
	//添加选择模式背景图e
	auto twomodeString = CSGSTXT::GET("twomode");
	auto createhomeString = CSGSTXT::GET("createhome");
	auto fastenterString = CSGSTXT::GET("fastenter");
	auto searchhomeString = CSGSTXT::GET("searchhome");
	//中文显示e

	//添加创建房间 快速加入 搜索房间三个按钮s
	btn_createhome = Button::create("Bg/btn_bg.png");
	btn_createhome->setPosition(Vec2(origin.x + visibleSize.width / 2 - 168 * 2, origin.y + 70));
	img_bg->addChild(btn_createhome);
	btn_createhome->addTouchEventListener(CC_CALLBACK_2(SelectMode::CreateHomePop, this));

	auto lab_createhome = Label::createWithTTF(createhomeString, "fonts/FZBWKSK.TTF",22);
	lab_createhome->setPosition(Vec2(origin.x + visibleSize.width / 2 - 168 * 2, origin.y + 70));
	img_bg->addChild(lab_createhome);

	btn_fastenter = Button::create("Bg/btn_bg.png");
	btn_fastenter->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 70));
	img_bg->addChild(btn_fastenter);
	btn_fastenter->addTouchEventListener(CC_CALLBACK_2(SelectMode::DidFastEnter, this));

	auto lab_fastenter = Label::createWithTTF(fastenterString, "fonts/FZBWKSK.TTF", 22);
	lab_fastenter->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 70));
	img_bg->addChild(lab_fastenter);

	btn_searchhome = Button::create("Bg/btn_bg.png");
	btn_searchhome->setPosition(Vec2(origin.x + visibleSize.width / 2 + 168 * 2, origin.y + 70));
	img_bg->addChild(btn_searchhome);
	btn_searchhome->addTouchEventListener(CC_CALLBACK_2(SelectMode::SearchHomePop, this));

	auto lab_searchhome = Label::createWithTTF(searchhomeString, "fonts/FZBWKSK.TTF", 22);
	lab_searchhome->setPosition(Vec2(origin.x + visibleSize.width / 2 + 168 * 2, origin.y + 70));
	img_bg->addChild(lab_searchhome);
	//添加创建房间 快速加入 搜索房间三个按钮e


	//添加回退按钮s
	btn_back = Button::create("Bg/back_bg.png");
	btn_back->setAnchorPoint(Vec2(0, 1));
	btn_back->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	img_bg->addChild(btn_back);

	btn_back->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			//切换场景s
			Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, HelloWorld::createScene()));
			break;
		}
	});
	//添加回退按钮e

	//添加2人对战模式s
	img_two = ui::ImageView::create("Mode/model_big_2.png");
	img_two->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_two);
	//添加2人对战模式e

	//添加6人对战模式s
	img_six = ui::ImageView::create("Mode/model_small_6.png");
	img_six->setPosition(Vec2(origin.x + visibleSize.width / 2 + 168 * 2, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_six);
	//添加6人对战模式e

	//添加当前模式标签s
	lab_slct_bg = ui::ImageView::create("Mode/model_label_bg.png");
	lab_slct_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 335 / 2));
	img_bg->addChild(lab_slct_bg);

	lab_slct_mode = Label::createWithTTF(twomodeString, "fonts/FZBWKSK.TTF", 36);
	lab_slct_mode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 335 / 2));
	img_bg->addChild(lab_slct_mode);
	//添加当前模式标签e

	//给对战模式添加点击事件s
	img_two->setTouchEnabled(true);
	img_two->addTouchEventListener(CC_CALLBACK_2(SelectMode::AutoSlide, this));
	img_two->setTag(2);
	img_six->setTouchEnabled(true);
	img_six->addTouchEventListener(CC_CALLBACK_2(SelectMode::AutoSlide, this));
	img_six->setTag(6);
	//给对战模式添加点击事件e

	return true;
}

void SelectMode::AutoSlide(Ref* pSender, Widget::TouchEventType type) {
	//log("click");

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Vec2 screenCenter = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

		ImageView* img_slct = (ImageView*)pSender;
		Vec2 slctPosNow = img_slct->getPosition();

		if (!slctPosNow.equals(screenCenter)) {
			auto move = MoveBy::create(0.5, screenCenter - slctPosNow);
			Sequence* seq2;
			Sequence* seq6;

			int i = img_slct->getTag();
			if (i == 2) {
				seq2 = Sequence::create(move, CallFuncN::create(CC_CALLBACK_1(SelectMode::change2ImageBig, this)), NULL);
				seq6 = Sequence::create(move->clone(), CallFuncN::create(CC_CALLBACK_1(SelectMode::change6ImageSmall, this)), NULL);
			}
			else if (i == 6) {
				seq2 = Sequence::create(move->clone(), CallFuncN::create(CC_CALLBACK_1(SelectMode::change2ImageSmall, this)), NULL);
				seq6 = Sequence::create(move->clone(), CallFuncN::create(CC_CALLBACK_1(SelectMode::change6ImageBig, this)), NULL);
			}
			img_two->runAction(seq2);
			img_six->runAction(seq6);
		}
		break;
	}
}

void SelectMode::change6ImageBig(Node* sender) {
	lab_slct_mode->setString(CSGSTXT::GET("sixmode"));

	((ImageView*)sender)->loadTexture("Mode/model_big_6.png");
}

void SelectMode::change6ImageSmall(Node* sender) {
	((ImageView*)sender)->loadTexture("Mode/model_small_6.png");
}

void SelectMode::change2ImageBig(Node* sender) {
	lab_slct_mode->setString(CSGSTXT::GET("twomode"));

	((ImageView*)sender)->loadTexture("Mode/model_big_2.png");
}

void SelectMode::change2ImageSmall(Node* sender) {
	((ImageView*)sender)->loadTexture("Mode/model_small_2.png");
}

void SelectMode::CreateHomePop(Ref* pSender, Widget::TouchEventType type) {

	Director* director = nullptr;
	Scene* homeScene = nullptr;
	TransitionSlideInR* transition = nullptr; //场景切换动画的一种

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//切换场景s
		Json::Value root;
		root[SRoom[ERoom_max_player_cnt]] = 2;
		std::shared_ptr<PPacket> p(new PPacket());
		p->body = root.toStyledString();
		p->pack(PLAYER_CREATE_ROOM);
		g_lstWrite.push_back(p);

		break;
	}
}

void SelectMode::DidFastEnter(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Json::Value root;
		std::shared_ptr<PPacket> p(new PPacket());
		p->body = root.toStyledString();
		p->pack(PLAYER_MATCH_ROOM_FAST);
		g_lstWrite.push_back(p);
		break;
	}
}

void SelectMode::SearchHomePop(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		auto searchHomeLayer = SearchHome::create();
		this->addChild(searchHomeLayer);
		break;
	}
}
