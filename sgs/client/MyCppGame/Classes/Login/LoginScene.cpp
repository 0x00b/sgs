#include "LoginScene.h"

USING_NS_CC;
using namespace ui;

Scene* Login::createScene()
{
	return Login::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoginScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Login::init()
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
	//Ìí¼Ó±³¾°s
	auto layer_bg = Layer::create();
	this->addChild(layer_bg);

	ImageView* img_bg = ImageView::create("Login/login_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	img_bg->setScale(visibleSize.width/img_bg->getContentSize().width, visibleSize.height / img_bg->getContentSize().height);
	layer_bg->addChild(img_bg);
	//Ìí¼Ó±³¾°e

	//±³¾°Í¼Æ¬´óÐ¡s
	Size size_bg = img_bg->getContentSize();
	//±³¾°Í¼Æ¬´óÐ¡e

	//¼ÓÔØÖÐÎÄxml
	ValueMap message = FileUtils::getInstance()->getValueMapFromFile("fonts/ChineseStrings.xml");
	//¼ÓÔØÖÐÎÄxml

	//µÇÂ¼¿òs
	ImageView* img_rect_bg = ImageView::create("Login/login_rect_bg.png");
	img_rect_bg->setPosition(Vec2(size_bg.width / 2, size_bg.height / 2));
	img_bg->addChild(img_rect_bg);

	Size size_rect_bg = img_rect_bg->getContentSize();
	//µÇÂ¼¿òe

	//ÕËºÅÃÜÂës
	Label* lab_account = Label::create(message["account"].asString(), "fonts/FZBWKSK.TTF", 22);
	lab_account->setPosition(Vec2(size_rect_bg.width / 5, size_rect_bg.height * 3 / 4));
	img_rect_bg->addChild(lab_account);

	ImageView* img_account_bg = ImageView::create("Bg/txt_bg.png");
	img_account_bg->setPosition(Vec2(lab_account->getPosition().x + 50, size_rect_bg.height * 3 / 4));
	img_account_bg->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(img_account_bg);

	txt_account = TextField::create();
	txt_account->setPlaceHolder("input your account");
	txt_account->setPosition(Vec2(lab_account->getPosition().x + 55, size_rect_bg.height * 3 / 4));
	txt_account->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(txt_account);

	Label* lab_pwd = Label::create(message["account"].asString(), "fonts/FZBWKSK.TTF", 22);
	lab_pwd->setPosition(Vec2(size_rect_bg.width / 5, size_rect_bg.height / 2));
	img_rect_bg->addChild(lab_pwd);

	ImageView* img_pwd_bg = ImageView::create("Bg/txt_bg.png");
	img_pwd_bg->setPosition(Vec2(lab_pwd->getPosition().x + 50, size_rect_bg.height / 2));
	img_pwd_bg->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(img_pwd_bg);

	txt_pwd = TextField::create();
	txt_pwd->setPlaceHolder("input your pwd");
	txt_pwd->setPasswordEnabled(true);
	txt_pwd->setPosition(Vec2(lab_pwd->getPosition().x + 55, size_rect_bg.height / 2));
	txt_pwd->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(txt_pwd);
	//ÕËºÅÃÜÂëe

	//µÇÂ¼°´Å¥s
	btn_login = Button::create("Bg/btn_bg.png");
	btn_login->setPosition(Vec2(size_rect_bg.width / 2, size_rect_bg.height / 5));
	img_rect_bg->addChild(btn_login);

	btn_login->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			//´Ë´¦ÁªÍø¼ì²éÕËºÅ 
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, HelloWorld::createScene()));

			log(txt_account->getString().c_str());
			log(txt_pwd->getString().c_str());
			break;
		}
	});

	Label* lab_login = Label::create(message["login"].asString(),"fonts/FZBWKSK.TTF",22);
	lab_login->setPosition(Vec2(size_rect_bg.width / 2, size_rect_bg.height / 5));
	img_rect_bg->addChild(lab_login);
	//µÇÂ¼°´Å¥e

	return true;
}