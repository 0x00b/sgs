#include "ReadyHomeScene2.h"

USING_NS_CC;
using namespace ui;


ReadyHome::~ReadyHome()
{

}

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

	//预加载图片s
	TextureCache::getInstance()->addImage("Home/generalface_soldier1.png");
	//预加载图片e

	//添加回退按钮s
	btn_back = Button::create("Bg/back_bg.png");
	btn_back->setAnchorPoint(Vec2(0, 1));
	btn_back->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	img_bg->addChild(btn_back);

	btn_back->addTouchEventListener(CC_CALLBACK_2(ReadyHome::DidBack, this));
	//添加回退按钮e

	//两个座位s
	img_table_bg[0] = ui::ImageView::create("Home/generalface_soldier1.png");
	img_table_bg[0]->setPosition(Vec2(origin.x + visibleSize.width / 2 - 172, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_table_bg[0]);

	lab_table_name[0] = Label::createWithTTF("","fonts/FZBWKSK.TTF",24);
	lab_table_name[0]->setPosition(Vec2(origin.x + visibleSize.width / 2 - 172, origin.y + visibleSize.height / 2 + 150));
	img_bg->addChild(lab_table_name[0]);

	img_table_bg[1] = ui::ImageView::create("Home/generalface_mystery.png");
	img_table_bg[1]->setPosition(Vec2(origin.x + visibleSize.width / 2 + 172, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_table_bg[1]);

	lab_table_name[1] = Label::createWithTTF("", "fonts/FZBWKSK.TTF", 24);
	lab_table_name[1]->setPosition(Vec2(origin.x + visibleSize.width / 2 + 172, origin.y + visibleSize.height / 2 + 150));
	img_bg->addChild(lab_table_name[1]);
	//两个座位s

	//房间号s
	lab_homeid = Label::createWithTTF("", "fonts/FZBWKSK.TTF", 36);
	lab_homeid->setPosition(Vec2(img_bg->getContentSize().width / 2, img_bg->getContentSize().height * 4 / 5));
	img_bg->addChild(lab_homeid);
	//房间号e

	//准备按钮s
	btn_ready = Button::create("Home/chapter_normal.png", "Home/chapter_selected.png", "Home/disabled_image.png");
	btn_ready->setTitleText(SGSTXT["ready"]);
	btn_ready->setTitleFontName("fonts/FZBWKSK.TTF");
	btn_ready->setTitleFontSize(40);

	btn_ready->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		Json::Value root;
		std::shared_ptr<PPacket> p(new PPacket());
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			if (btn_ready->getTitleText() == SGSTXT["cancel"]) {	//准备
				btn_ready->setTitleText(SGSTXT["ready"]);
				root["ready"] = true;
			}
			else if (btn_ready->getTitleText() == SGSTXT["ready"]) {	//取消准备
				btn_ready->setTitleText(SGSTXT["cancel"]);
				btn_ready->setTitleText(SGSTXT["ready"]);
				root["ready"] = false;
			}

			p->body = root.toStyledString();
			p->pack(PLAYER_READY);
			g_lstWrite.push_back(p);
		default:
			break;
		}
	});
	btn_ready->setPosition(Vec2(origin.x + visibleSize.width - 150, origin.y + visibleSize.height / 2));
	img_bg->addChild(btn_ready);
	//准备按钮e

	UpdateReadyHome();

	return true;
}

void ReadyHome::DidBack(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//退出房间消息s
		Json::Value root;
		std::shared_ptr<PPacket> p(new PPacket());
		p->body = root.toStyledString();
		p->pack(PLAYER_QUIT_ROOM);
		g_lstWrite.push_back(p);
		//退出房间消息e

		auto director = Director::getInstance();
		auto SelectModeScene = SelectMode::createScene();
		director->replaceScene(TransitionSlideInL::create(0.5f, SelectModeScene));
		break;
	}
}

void ReadyHome::UpdateReadyHome() {
	lab_homeid->setString(std::to_string(u_room.m_nRoomID));	//显示房间号
	for (int i = 0; i < 2;i++) {
		lab_table_name[i]->setString("");
		img_table_bg[i]->loadTexture("Home/generalface_mystery.png");
	}
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
	{
		lab_table_name[(*it).m_nSeatId]->setString((*it).m_stAccount);
		img_table_bg[(*it).m_nSeatId]->loadTexture("Home/generalface_soldier1.png");
	}
}