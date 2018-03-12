#include "RegisterScene.h"

USING_NS_CC;
using namespace ui;

extern std::list<std::shared_ptr<PPacket>> g_lstWrite;

Scene* Register::createScene()
{
	return Register::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoginScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Register::init()
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
	img_bg->setScale(visibleSize.width / img_bg->getContentSize().width, visibleSize.height / img_bg->getContentSize().height);
	layer_bg->addChild(img_bg);
	//Ìí¼Ó±³¾°e

	//±³¾°Í¼Æ¬´óÐ¡s
	Size size_bg = img_bg->getContentSize();
	//±³¾°Í¼Æ¬´óÐ¡e

	//µÇÂ¼¿òs
	ImageView* img_rect_bg = ImageView::create("Login/login_rect_bg.png");
	img_rect_bg->setPosition(Vec2(size_bg.width / 2, size_bg.height / 2));
	img_bg->addChild(img_rect_bg);

	Size size_rect_bg = img_rect_bg->getContentSize();

	ImageView* zhedang = ImageView::create("chapter_general_1.png");
	zhedang->setAnchorPoint(Vec2(0.5, 0.1));
	zhedang->setPosition(Vec2(size_rect_bg.width / 2, size_rect_bg.height));
	img_rect_bg->addChild(zhedang);
	zhedang->setTouchEnabled(true);
	zhedang->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, Login::createScene()));
			break;
		}
	});
	//µÇÂ¼¿òe

	//ÕËºÅÃÜÂës
	Label* lab_account = Label::create(CSGSTXT::GET("account"), "fonts/FZBWKSK.TTF", 22);
	lab_account->setPosition(Vec2(size_rect_bg.width / 5, size_rect_bg.height * 4 / 5));
	img_rect_bg->addChild(lab_account);

	ImageView* img_account_bg = ImageView::create("Bg/txt_bg.png");
	img_account_bg->setPosition(Vec2(lab_account->getPosition().x + 50, size_rect_bg.height * 4 / 5));
	img_account_bg->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(img_account_bg);

	txt_account = TextField::create();
	txt_account->setPlaceHolder("input your account");
	txt_account->setPosition(Vec2(lab_account->getPosition().x + 55, size_rect_bg.height * 4 / 5));
	txt_account->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(txt_account);

	Label* lab_pwd = Label::create(CSGSTXT::GET("pwd"), "fonts/FZBWKSK.TTF", 22);
	lab_pwd->setPosition(Vec2(size_rect_bg.width / 5, size_rect_bg.height * 3 / 5));
	img_rect_bg->addChild(lab_pwd);

	ImageView* img_pwd_bg = ImageView::create("Bg/txt_bg.png");
	img_pwd_bg->setPosition(Vec2(lab_pwd->getPosition().x + 50, size_rect_bg.height * 3 / 5));
	img_pwd_bg->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(img_pwd_bg);

	txt_pwd = TextField::create();
	txt_pwd->setPlaceHolder("input your pwd");
	txt_pwd->setPasswordEnabled(true);
	txt_pwd->setPosition(Vec2(lab_pwd->getPosition().x + 55, size_rect_bg.height * 3 / 5));
	txt_pwd->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(txt_pwd);

	Label* lab_pwd_again = Label::create(CSGSTXT::GET("pwdagain"), "fonts/FZBWKSK.TTF", 22);
	lab_pwd_again->setPosition(Vec2(size_rect_bg.width / 5, size_rect_bg.height * 2 / 5));
	img_rect_bg->addChild(lab_pwd_again);

	ImageView* img_pwd_bg_again = ImageView::create("Bg/txt_bg.png");
	img_pwd_bg_again->setPosition(Vec2(lab_pwd->getPosition().x + 50, size_rect_bg.height * 2 / 5));
	img_pwd_bg_again->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(img_pwd_bg_again);

	txt_pwd_again = TextField::create();
	txt_pwd_again->setPlaceHolder("input your pwd again");
	txt_pwd_again->setPasswordEnabled(true);
	txt_pwd_again->setPosition(Vec2(lab_pwd->getPosition().x + 55, size_rect_bg.height * 2 / 5));
	txt_pwd_again->setAnchorPoint(Vec2(0, 0.5));
	img_rect_bg->addChild(txt_pwd_again);
	//ÕËºÅÃÜÂëe

	//×¢²á°´Å¥s
	btn_register = Button::create("Bg/btn_bg.png");
	btn_register->setPosition(Vec2(size_rect_bg.width / 2, size_rect_bg.height / 5));
	img_rect_bg->addChild(btn_register);

	btn_register->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			if (txt_pwd->getString() == txt_pwd_again->getString()){
				if (txt_account->getStringLength() >= 3 && txt_account->getStringLength() <= 15 &&
					txt_pwd->getStringLength() >= 3 && txt_pwd->getStringLength() <= 15) {
					//´Ë´¦ÁªÍø¼ì²éÕËºÅs
					Json::Value root;
					root[SJPROTO[E_Player]][SPlayer[EPlayer_account]] = txt_account->getString();
					root[SJPROTO[E_Player]][SPlayer[EPlayer_passwd]] = txt_pwd->getString();
					std::shared_ptr<PPacket> p(new PPacket());
					p->body = root.toStyledString();
					p->pack(PLAYER_REGIST);
					g_lstWrite.push_back(p);
					//´Ë´¦ÁªÍø¼ì²éÕËºÅe
				}
				else {
					MessageBox("please check your input!", "");
				}
			}
			else {
				MessageBox("password is not equal!", "");
			}

			break;
		}
	});

	Label* lab_register = Label::create(CSGSTXT::GET("register"), "fonts/FZBWKSK.TTF", 22);
	lab_register->setPosition(Vec2(size_rect_bg.width / 2, size_rect_bg.height / 5));
	img_rect_bg->addChild(lab_register);
	//×¢²á°´Å¥e

	return true;
}