#include "SelectModeScene.h"

USING_NS_CC;

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
	//��ӱ���s
	auto layer_bg = Layer::create();
	this->addChild(layer_bg);

	ui::ImageView* img_bg = ui::ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//����Ĵ���������ͼƬǡ�ó�����Ļ ������Ϊ�������ű�����ͬ ������ͼƬ����
	//img_bg->setScale(visibleSize.width/img_bg->getContentSize().width, visibleSize.height / img_bg->getContentSize().height);
	layer_bg->addChild(img_bg);
	//��ӱ���e

	//���ѡ��ģʽ����ͼs
	ui::ImageView* img_slct_bg = ui::ImageView::create("Mode/model_select_bg.png");
	img_slct_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_slct_bg);
	//���ѡ��ģʽ����ͼe

	//������ʾs
	//��ʱ
	//Dictionary* message = Dictionary::createWithContentsOfFile("fonts/ChineseStrings.xml");
	//auto sixmodeValue = message->valueForKey("sixmode");    //����key����ȡvalue
	//const char* sixmodeString = sixmodeValue->getCString();    //��valueת��Ϊ�ַ���
	//���
	ValueMap message = FileUtils::getInstance()->getValueMapFromFile("fonts/ChineseStrings.xml");
	auto twomodeString = message["twomode"].asString();
	auto createhomeString = message["createhome"].asString();
	auto fastenterString = message["fastenter"].asString();
	auto searchhomeString = message["searchhome"].asString();
	//������ʾe

	//��Ӵ������� ���ټ��� ��������������ťs
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
	//��Ӵ������� ���ټ��� ��������������ťe


	//��ӻ��˰�ťs
	btn_back = Button::create("Bg/back_bg.png");
	btn_back->setAnchorPoint(Vec2(0, 1));
	btn_back->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	img_bg->addChild(btn_back);

	btn_back->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			//�л�����s
			Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, HelloWorld::createScene()));
			break;
		}
	});
	//��ӻ��˰�ťe

	//���2�˶�սģʽs
	img_two = ui::ImageView::create("Mode/model_big_2.png");
	img_two->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_two);
	//���2�˶�սģʽe

	//���6�˶�սģʽs
	img_six = ui::ImageView::create("Mode/model_small_6.png");
	img_six->setPosition(Vec2(origin.x + visibleSize.width / 2 + 168 * 2, origin.y + visibleSize.height / 2));
	img_bg->addChild(img_six);
	//���6�˶�սģʽe

	//��ӵ�ǰģʽ��ǩs
	lab_slct_bg = ui::ImageView::create("Mode/model_label_bg.png");
	lab_slct_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 335 / 2));
	img_bg->addChild(lab_slct_bg);

	lab_slct_mode = Label::createWithTTF(twomodeString, "fonts/FZBWKSK.TTF", 36);
	lab_slct_mode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 335 / 2));
	img_bg->addChild(lab_slct_mode);
	//��ӵ�ǰģʽ��ǩe

	//����սģʽ��ӵ���¼�s
	img_two->setTouchEnabled(true);
	img_two->addTouchEventListener(CC_CALLBACK_2(SelectMode::AutoSlide, this));
	img_two->setTag(2);
	img_six->setTouchEnabled(true);
	img_six->addTouchEventListener(CC_CALLBACK_2(SelectMode::AutoSlide, this));
	img_six->setTag(6);
	//����սģʽ��ӵ���¼�e

	return true;
}

void SelectMode::AutoSlide(Ref* pSender, Widget::TouchEventType type) {
	log("click");

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
	ValueMap message = FileUtils::getInstance()->getValueMapFromFile("fonts/ChineseStrings.xml");
	auto sixmodeString = message["sixmode"].asString();
	lab_slct_mode->setString(sixmodeString);

	((ImageView*)sender)->loadTexture("Mode/model_big_6.png");
}

void SelectMode::change6ImageSmall(Node* sender) {
	((ImageView*)sender)->loadTexture("Mode/model_small_6.png");
}

void SelectMode::change2ImageBig(Node* sender) {
	ValueMap message = FileUtils::getInstance()->getValueMapFromFile("fonts/ChineseStrings.xml");
	auto twomodeString = message["twomode"].asString();
	lab_slct_mode->setString(twomodeString);

	((ImageView*)sender)->loadTexture("Mode/model_big_2.png");
}

void SelectMode::change2ImageSmall(Node* sender) {
	((ImageView*)sender)->loadTexture("Mode/model_small_2.png");
}

void SelectMode::CreateHomePop(Ref* pSender, Widget::TouchEventType type) {

	Director* director = nullptr;
	Scene* homeScene = nullptr;
	TransitionSlideInR* transition = nullptr; //�����л�������һ��

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//�л�����s
		director = Director::getInstance();
		homeScene = ReadyHome::createScene();
		transition = TransitionSlideInR::create(0.5f, homeScene);
		director->replaceScene(transition);
		break;
	}
}

void SelectMode::DidFastEnter(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:

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
