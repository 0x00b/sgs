#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <fstream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
	if (!Scene::init())
	{
		return false;
	}
	auto layer = Layer::create();
	if (!Scene::init())
	{
		return false;
	}
	layer->init();

	fstream _file;
	_file.open("res/HeroDetail.txt",ios::in);
	if (!_file)
	{
		Json::Value root;
		std::shared_ptr<PPacket> p(new PPacket());
		p->body = root.toStyledString();
		p->pack(GAME_HERO_DETAIL);
		g_lstWrite.push_back(p);
		;  //�����ڷ�����Ϣ��������
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Size mywinsize = Director::getInstance()->getWinSize();
	//	Size mywinsize = visibleSize;
	float winw = mywinsize.width; //��ȡ��Ļ���
	float winh = mywinsize.height;//��ȡ��Ļ�߶�

	auto bg_sprite = Sprite::create("res/scene_bg.png");
	auto bg_head = Sprite::create("res/userInfoBar_string.png");
	auto bg_foot = Sprite::create("res/userFootBar_string.png");

	float spx_bg_head = bg_head->getContentSize().width;
	float spy_bg_head = bg_head->getContentSize().height;
	bg_head->setScaleX(winw / spx_bg_head); //���þ��������ű���
	bg_head->setScaleY(winh / 12 / spy_bg_head);
	bg_foot->setScaleX(winw / spx_bg_head);
	bg_foot->setScaleY(winh / 12 / spy_bg_head);

	bg_head->setAnchorPoint(Point(0, 1));
	bg_head->setPosition(0, winh);
	bg_foot->setAnchorPoint(Point(0, 0));
	bg_foot->setPosition(0, 0);
	bg_sprite->setPosition(0, 0);
	bg_sprite->setAnchorPoint(Point(0, 0));

								  //	float spx1 = backGround->getTextureRect().getMaxX();
								  //	float spy1 = backGround->getTextureRect().getMaxY();
	float spx = bg_sprite->getContentSize().width;
	float spy = bg_sprite->getContentSize().height;

	bg_sprite->setScaleX(winw / spx); //���þ��������ű���
	bg_sprite->setScaleY(winh / spy);

	addChild(bg_sprite);
	addChild(bg_head);
	addChild(bg_foot);


	auto sprite = Sprite::create();
	auto sprite1 = Sprite::create();
	//��ǰһ���ľ����¼�����Ž�ȥ

	auto cache = SpriteFrameCache::getInstance();  // ����һ�����浥��
	auto cache1 = SpriteFrameCache::getInstance();  // ����һ�����浥��
	cache->addSpriteFramesWithFile("ShenFenChang/ShenFenChang0.plist");   //ͨ��plist�����ļ����һ�龫��֡
	cache1->addSpriteFramesWithFile("ShenFenChang/ShenFenChang1.plist");
	Vector<SpriteFrame*> vec, vec1, vec2, vec3;
	char name[50];
	memset(name, 0, 50);
	for (int i = 0; i <= 4; i++)
	{
		sprintf(name, "caipimoshitupiao_0000%d.png", i);
		vec.pushBack(cache->getSpriteFrameByName(name));
	}  //�Ѵ��ͼһ����һ���ֵ��г����Ž�vec
	for (int i = 5; i <= 7; i++)
	{
		sprintf(name, "caipimoshitupiao_0000%d.png", i);
		vec.pushBack(cache1->getSpriteFrameByName(name));
	}  //�Ѵ��ͼһ����һ���ֵ��г����Ž�vec
	Animation *animation = Animation::createWithSpriteFrames(vec, 0.1f);  //����������
	Animate *animate = Animate::create(animation); //��װ�ɶ���


	sprite->runAction(RepeatForever::create(animate));


	cache1->removeUnusedSpriteFrames();
	cache1->addSpriteFramesWithFile("ShenFenChang/ShenFenChang0.plist");   //ͨ��plist�����ļ����һ�龫��֡
	memset(name, 0, 50);
	for (int i = 0; i < 8; i++)
	{
		sprintf(name, "caipimoshitu_0000%d.png", i);
		vec1.pushBack(cache->getSpriteFrameByName(name));
	}  //�Ѵ��ͼһ����һ���ֵ��г����Ž�vec
	animation = Animation::createWithSpriteFrames(vec1, 0.1f);  //����������
	animate = Animate::create(animation); //��װ�ɶ���

	memset(name, 0, 50);
	sprintf(name, "caipimoshitu_00001.png");
	SpriteFrame* sa = cache->getSpriteFrameByName(name);
	Rect b_r_sa = sa->getRect();
	sprite1->runAction(RepeatForever::create(animate));


	cache->removeUnusedSpriteFrames();
	cache->addSpriteFramesWithFile("ShenFenChang/ShenFenChang1.plist");   //ͨ��plist�����ļ����һ�龫��֡
	memset(name, 0, 50);

	sprintf(name, "caipimoshitu.png");
	vec2.pushBack(cache->getSpriteFrameByName(name));

	SpriteFrame* background = cache->getSpriteFrameByName(name);
	Rect b_r = background->getRect();
	Sprite* sprite7 = Sprite::createWithSpriteFrame(background);
	sprite7->setAnchorPoint(Point(0, 0));
	sprite7->setPosition(0, 0);
	float size_scale;
	size_scale = 0.8*visibleSize.height / b_r.size.width;
	Size sprite7_size = sprite7->getContentSize();

	cocos2d::ui::Button*  button_all[3];
	Size size_all[3];  //3��ͼԭ���Ĵ�С
	
	int num;
	char name_pic[30];
	char name2_pic[30];
	for (num = 0; num < 3; num++)
	{
		sprintf(name_pic, "res/model_btn_%d.png", num + 1);  //   \\ת��
		sprintf(name2_pic, "res/model_btn_%d.png", num + 1);
		button_all[num] = cocos2d::ui::Button::create(name_pic, name2_pic, name_pic);
		size_all[num] = button_all[num]->getCustomSize();
	}

	Point four_position[4];  //4����Ķ�λ
	four_position[0] = Point(visibleSize.width / 12, visibleSize.height / 12);
	four_position[2] = Point(four_position[0].x + b_r.size.height*size_scale + size_all[0].width*size_scale, visibleSize.height / 12);
	four_position[3] = Point(four_position[2].x + size_all[1].width*size_scale, visibleSize.height / 12);  //size_scale���Ǹ�����ͼ����������Ļ0.8����Ҫ��ϵ��

	for (num = 0; num < 3; num++)
	{
		button_all[num]->setAnchorPoint(Point(0, 0));
		button_all[num]->setScale(size_scale);
	}

	//size_scale = visibleSize;
	sprite7->setScale(size_scale);
	sprite7->setAnchorPoint(Point(0, 0));
	sprite7->setRotation(270);
	sprite7->setAnchorPoint(Point(0, 1));
	sprite7->setPosition(visibleSize.width / 12 + size_all[0].width*size_scale, visibleSize.height/12);

	sprite->setScale(size_scale);
	sprite->setAnchorPoint(Point(1, 1));
	sprite->setPosition(b_r.size.height*size_scale+ visibleSize.width / 12 + size_all[0].width*size_scale, b_r.size.width*size_scale*0.865+ visibleSize.height / 12);


	float ac_picture = b_r.size.width / b_r_sa.size.height;
	sprite1->setScale(ac_picture*size_scale);
	sprite1->setAnchorPoint(Point(0, 0));
	sprite1->setPosition(visibleSize.width / 12 + size_all[0].width*size_scale, visibleSize.height / 12);
		

	addChild(sprite7);
	addChild(sprite);
	addChild(sprite1);	

	auto touchHandCardListener = EventListenerTouchOneByOne::create();//��ָ�������� Ҳ�ж�����
	touchHandCardListener->setSwallowTouches(true);//�����¼���û �¼��ַ�����
	touchHandCardListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchHandCardBegan, this);
	touchHandCardListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchHandCardMoved, this);
	touchHandCardListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchHandCardEnded, this);
	//���¼��󶨵��ؼ���
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchHandCardListener->clone(), sprite1);

	button_all[0]->setPosition(four_position[0]);
	button_all[1]->setPosition(four_position[2]);
	button_all[2]->setPosition(four_position[3]);
	addChild(button_all[0]);
	addChild(button_all[1]);
	addChild(button_all[2]);

	button_all[0]->addTouchEventListener(([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, SelectMode::createScene()));
			break;
		}
	}));

	auto listener_loginPicture = EventListenerTouchOneByOne::create();
	listener_loginPicture->onTouchBegan = [sprite1](Touch *t, Event *event)
	{
		if (sprite1->getBoundingBox().containsPoint(t->getLocation()))
		{

			//using boost::asio::ip::tcp;
			//log("a");
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_loginPicture, sprite1);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


bool HelloWorld::onTouchHandCardBegan(Touch* touch, Event* event) {
	//���������
	auto target = (ImageView*)event->getCurrentTarget();
	//���������ת����Ŀ������ϵ��ȥ
	Vec2 touchPos = touch->getLocation();
	Vec2 locationInNode = target->convertToNodeSpace(touchPos);
	//����һ��Ŀ�����ľ���
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	//�жϵ���Ƿ�����Ŀ�������
	if (rect.containsPoint(locationInNode)) {
		return true;
	}
	else {
		return false;
	}
}

void HelloWorld::onTouchHandCardMoved(Touch* touch, Event* event) {

}

bool HelloWorld::onTouchHandCardEnded(Touch* touch, Event* event) {
	Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, HeroDetail::createScene()));
	return true;
}