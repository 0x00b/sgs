#include "CardInfoScene.h"

USING_NS_CC;
using namespace ui;

Scene* CardInfo::createScene()
{
	return CardInfo::create();

}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SearchHomeLayer.cpp\n");
}

// on "init" you need to initialize your instance
bool CardInfo::init()
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
	// 添加地图容器s
	img_map = ImageView::create("map.png");
	//？？？？？？下面这一句不起作用，所以我在上面直接做了一张1334*1800的图 为什么不起作用 待解决
	img_map->setAnchorPoint(Vec2(0.5, 0.5));
	img_map->setPosition(Vec2(visibleSize.width/2, 750 - 900));
	this->addChild(img_map);
	// 添加地图容器e

	// 给背景容器添加拖拽事件s
	auto touchMapListener = EventListenerTouchOneByOne::create();//单指操作监听 也有多点操作
	touchMapListener->setSwallowTouches(true);//设置事件吞没 事件分发机制
	touchMapListener->onTouchBegan = CC_CALLBACK_2(CardInfo::onTouchMapBegan, this);
	touchMapListener->onTouchMoved = CC_CALLBACK_2(CardInfo::onTouchMapMoved, this);
	touchMapListener->onTouchEnded = CC_CALLBACK_2(CardInfo::onTouchMapEnded, this);
	//将事件绑定到控件上
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchMapListener, img_map);
	// 给背景容器添加拖拽事件e

	//卡牌添加到背景上s
	for (int i = 0; i < 32; ++i) {
		if (i == 13 || i == 16) continue;

		int t = i;
		if (i > 16) t -= 2;
		else if (i > 13) t -= 1;

		char name[12];
		snprintf(name,12, "%02x", i);
		btn_cards[t] = Button::create(std::string("Fight/card/") + name + ".png");
		btn_cards[t]->setAnchorPoint(Vec2(0,0));
		btn_cards[t]->setPosition(Vec2((200+19) * (t % 6) + 19, (290 + 58) * (t / 6) + 58));
		img_map->addChild(btn_cards[t]);
		btn_cards[t]->setTag(i);
		btn_cards[t]->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			int tag;
			Vec2 diff;
			Vec2 posSrc;
			Vec2 posDes;
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				if (lab_card_detail != NULL) 
					lab_card_detail->removeFromParentAndCleanup(true);
				old_y = ((Button*)sender)->getTouchBeganPosition().y;
				flag = false;
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				if (flag) {
					old_y = ((Button*)sender)->getTouchMovePosition().y;
					flag = false;
				}
				else {
					flag = true;
				}
				diff = Vec2(0, 2*(((Button*)sender)->getTouchMovePosition().y - old_y));
				posSrc = img_map->getPosition();
				posDes = posSrc + diff;

				if (posDes.y > 900) {
					posDes.y = 900;
				}

				if (posDes.y < 750 - 900) {
					posDes.y = 750 - 900;
				}
				//超出屏幕的处理e

				img_map->setPosition(posDes);
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				tag = ((Button*)sender)->getTag();
				char name_xml[12];
				snprintf(name_xml, 12, "%02x", tag);
				lab_card_detail = Label::createWithTTF(CSGSTXT::GET(name_xml),"fonts/FZBWKSK.TTF",18);
				lab_card_detail->setTextColor(ccc4(255,0,0,255));
				lab_card_detail->setAnchorPoint(Vec2(0.5,0.5));
				lab_card_detail->setPosition(((Button*)sender)->getPosition().x+ ((Button*)sender)->getContentSize().width / 2, \
					((Button*)sender)->getPosition().y + ((Button*)sender)->getContentSize().height / 2);
				lab_card_detail->setDimensions(230,348);
				img_map->addChild(lab_card_detail);
			
				break;
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				lab_card_detail = NULL;
				break;
			default:
				break;
			}
		});
	}
	//卡牌添加到背景上e

	//添加回退按钮s
	btn_back = Button::create("Bg/back_bg.png");
	btn_back->setAnchorPoint(Vec2(0, 1));
	btn_back->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	this->addChild(btn_back);

	btn_back->addTouchEventListener(CC_CALLBACK_2(CardInfo::DidBack, this));
	//添加回退按钮e


	return true;
}

bool CardInfo::onTouchMapBegan(Touch* touch, Event* event) {
	return true;//事件分发机制
				//true会接着执行后面的move 和 end
				//可以理解为 true代表该控件要吞没 要消耗这个事件
				//否者就设置为不吞没 点击坐标下所有所在的控件都有机会接收到事件
}

void CardInfo::onTouchMapMoved(Touch* touch, Event* event) {
	Vec2 diff = touch->getDelta();	//从按下到当前移动的距离
	diff = Vec2(0, diff.y);
	Vec2 posSrc = img_map->getPosition();
	Vec2 posDes = posSrc + diff;

	if (posDes.y > 900) {
		posDes.y = 900;
	}

	if (posDes.y < 750 - 900) {
		posDes.y = 750 - 900;
	}
	//超出屏幕的处理e
	
	img_map->setPosition(posDes);
}

bool CardInfo::onTouchMapEnded(Touch* touch, Event* event) {
	return true;
}

void CardInfo::DidBack(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, HelloWorld::createScene()));
		break;
	}
}