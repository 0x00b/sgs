#include "FightMainScene.h"

USING_NS_CC;
using namespace ui;

Scene* FightMain::createScene()
{
	return FightMain::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in FightMainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FightMain::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	//animation_sha = Sprite::create("Bg/back_bg.png");
	animation_sha = Sprite::create();
	animation_shan = Sprite::create();
	animation_tao = Sprite::create();
	animation_sha->setAnchorPoint(Point(0, 0));
	animation_shan->setAnchorPoint(Point(0, 0));
	animation_tao->setAnchorPoint(Point(0, 0));

	animation_sha->setPosition(200, 300);
	animation_shan->setPosition(200, 300);
	animation_tao->setPosition(200, 300);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	win  = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...
	// 3. add your codes below...
	//背景层s
	Layer* layer_bg = Layer::create();
	this->addChild(layer_bg);
	//背景层e

	//背景图s
	img_bg = ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer_bg->addChild(img_bg);
	//背景图e

	//添加一个复选框 用于控制背景音乐s
	CheckBox* cb_bg_music = CheckBox::create("Sound/check_box_normal.png",
		"Sound/check_box_normal_press.png",
		"Sound/check_box_active.png",
		"Sound/check_box_normal_disable.png",
		"Sound/check_box_active_disable.png");
	cb_bg_music->setAnchorPoint(Vec2(1, 1));
	cb_bg_music->setPosition(Vec2(origin.x+visibleSize.width - 10,origin.y+visibleSize.height - 10));
	img_bg->addChild(cb_bg_music);
	cb_bg_music->setScale(0.5);
	cb_bg_music->setSelected(true);

	cb_bg_music->addEventListener([](Ref* pSender, CheckBox::EventType type) {
		switch (type)
		{
		case cocos2d::ui::CheckBox::EventType::SELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			break;
		case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			break;
		default:
			break;
		}
	});//注意这里监听器不是触摸监听器

	Label* lab_bg_music = Label::createWithTTF(CSGSTXT::GET("bgmusic"),"fonts/FZBWKSK.TTF",18);
	lab_bg_music->setAnchorPoint(Vec2(1,1));
	lab_bg_music->setPosition(Vec2(origin.x + visibleSize.width - 10 - cb_bg_music->getContentSize().width, origin.y + visibleSize.height - 10));
	img_bg->addChild(lab_bg_music);
	//添加一个复选框 用于控制背景音乐e

	i_current_card_num = 0;	//初始化手牌数为0

	selectHero = SelectHero2Layer::create();
	this->addChild(selectHero,2,"selectHero");
	Vec_create();  //当桃闪杀放入缓冲区
	addChild(animation_sha);
	addChild(animation_shan);
	addChild(animation_tao);
	return true;
}

void FightMain::InitHeroInfo() {
	//初始化当前阶段
	stage = 0;
	//初始化当前选中手牌
	status = 0;
	for (int i = 0; i < 20; ++i) {
		i_current_card[i] = -1;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始化敌我武将信息
	int i = 0;
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); i++,++it)
	{
		if (u_player.m_nSeatId == (*it).m_nSeatId) {
			//右下角我方武将s
			img_hero[0] = ImageView::create(std::string("Fight/hero_big/") + m_to_string((*it).m_oGameAttr.m_pHero->idhero) + ".png");
			img_hero[0]->setAnchorPoint(Vec2(1, 0));
			img_hero[0]->setPosition(Vec2(origin.x + visibleSize.width, 0));
			img_bg->addChild(img_hero[0]);

			img_hero_info_bg[0] = ImageView::create(std::string("Fight/info_bg_") + m_to_string((*it).m_oGameAttr.m_pHero->country) + ".png");
			img_hero_info_bg[0]->setAnchorPoint(Vec2(0, 1));
			img_hero_info_bg[0]->setPosition(Vec2(0, img_hero[0]->getContentSize().height));
			img_hero[0]->addChild(img_hero_info_bg[0]);
			img_hero_info_bg[0]->setScaleX(2);
			img_hero_info_bg[0]->setScaleY(3);

			img_hero_country[0] = ImageView::create(std::string("Fight/country_zi_") + m_to_string((*it).m_oGameAttr.m_pHero->country) + ".png");
			img_hero_country[0]->setAnchorPoint(Vec2(0, 1));
			img_hero_country[0]->setPosition(Vec2(0, img_hero[0]->getContentSize().height));
			img_hero[0]->addChild(img_hero_country[0]);

			lab_hero_name[0] = Label::createWithTTF(CSGSTXT::GET(m_to_string((*it).m_oGameAttr.m_pHero->idhero).c_str()), "fonts/FZBWKSK.TTF", 36);
			lab_hero_name[0]->setTextColor(ccc4(0, 0, 0, 255));
			lab_hero_name[0]->setAnchorPoint(Vec2(0, 1));
			lab_hero_name[0]->setPosition(Vec2(10, img_hero[0]->getContentSize().height - img_hero_country[0]->getContentSize().height));
			img_hero[0]->addChild(lab_hero_name[0]);

			img_handcard_num_bg[0] = ImageView::create("Fight/handcard_bg.png");
			img_handcard_num_bg[0]->setAnchorPoint(Vec2(1, 0));
			img_handcard_num_bg[0]->setPosition(Vec2(img_hero[0]->getContentSize().width, 0));
			img_hero[0]->addChild(img_handcard_num_bg[0]);

			lab_handcard_num[0] = Label::createWithTTF("0", "fonts/FZBWKSK.TTF", 50);
			lab_handcard_num[0]->setTextColor(ccc4(0, 0, 0, 255));
			lab_handcard_num[0]->setPosition(Vec2(img_handcard_num_bg[0]->getContentSize().width / 2, img_handcard_num_bg[0]->getContentSize().height / 2));
			img_handcard_num_bg[0]->addChild(lab_handcard_num[0]);

			for (int i = 0; i < (*it).m_oGameAttr.m_pHero->blood; i++) {
				img_blood[0][i] = ImageView::create("Fight/blood_have.png");
				img_blood[0][i]->setAnchorPoint(Vec2(1, 1));
				img_blood[0][i]->setPosition(Vec2(img_hero[0]->getContentSize().width - img_blood[0][i]->getContentSize().width * 2 * i - 5, img_hero[0]->getContentSize().height - 5));
				img_hero[0]->addChild(img_blood[0][i]);
				img_blood[0][i]->setScale(2);
			}

			img_hero[0]->setScale(visibleSize.width / 8 / img_hero[0]->getContentSize().width);	//武将信息缩放到宽度1/8
			//右下角我方武将e

			//我方出手定时s
			Sprite* sp_pt_my = Sprite::create("Fight/progress_timebar.png");
			pt_0 = ProgressTimer::create(sp_pt_my);
			pt_0->setScaleX(visibleSize.width / 2 / pt_0->getContentSize().width);
			pt_0->setScaleY(0.1);
			pt_0->setAnchorPoint(Vec2(0.5, 0.5));
			pt_0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.3));
			img_bg->addChild(pt_0);

			pt_0->setType(ProgressTimer::Type::BAR);	//条形进度条
			pt_0->setMidpoint(Vec2(0, 1));	//中心位置
			pt_0->setBarChangeRate(Vec2(1, 0));	//用作条形进度条显示的图片所占比例

			//pt_0->runAction(ProgressFromTo::create(15.0f, 100.0f, 0.0f)); //执行动画
			//我方出手定时e

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*img_hero[0]->loadTexture(std::string("Fight/hero_big/") + m_to_string((*it).m_oGameAttr.m_pHero->idhero) + ".png");
			img_hero_info_bg[0]->loadTexture(std::string("Fight/info_bg_")+m_to_string((*it).m_oGameAttr.m_pHero->country)+".png");
			img_hero_country[0]->loadTexture(std::string("Fight/country_zi_") + m_to_string((*it).m_oGameAttr.m_pHero->country) + ".png");
			lab_hero_name[0]->setString(CSGSTXT::GET(m_to_string((*it).m_oGameAttr.m_pHero->idhero).c_str()));
			lab_handcard_num[0]->setString("0");*/

			//显示当前阶段s
			lab_now_stage = Label::createWithTTF("","fonts/FZBWKSK.TTF",36);
			lab_now_stage->setPosition(pt_0->getPosition() - Vec2(0, 30));
			img_bg->addChild(lab_now_stage);
			//显示当前阶段s


			//选中手牌时的确定 取消按钮s
			btn_confirm = Button::create("Bg/btn_bg.png");
			btn_confirm->setPosition(pt_0->getPosition() - Vec2(btn_confirm->getContentSize().width * 1.5, 30));
			img_bg->addChild(btn_confirm);
			btn_confirm->setTitleText(CSGSTXT::GET("confirm"));
			btn_confirm->setTitleFontName("fonts/FZBWKSK.TTF");
			btn_confirm->setTitleFontSize(36);

			btn_cancel = Button::create("Bg/btn_bg.png");
			btn_cancel->setPosition(pt_0->getPosition() - Vec2(-btn_confirm->getContentSize().width * 1.5, 30));
			img_bg->addChild(btn_cancel);
			btn_cancel->setTitleText(CSGSTXT::GET("cancel"));
			btn_cancel->setTitleFontName("fonts/FZBWKSK.TTF");
			btn_cancel->setTitleFontSize(36);

			btn_confirm->addTouchEventListener(CC_CALLBACK_2(FightMain::btn_confirm_card, this));
			btn_cancel->addTouchEventListener(CC_CALLBACK_2(FightMain::btn_cancel_card, this));

			btn_confirm->setVisible(false);
			btn_cancel->setVisible(false);
			//选中手牌时的确定 取消按钮e
		}
		else {
			//中上方敌方武将s
			img_hero[1] = ImageView::create(std::string("Fight/hero_big/") + m_to_string((*it).m_oGameAttr.m_pHero->idhero) + ".png");
			img_hero[1]->setAnchorPoint(Vec2(0.5, 1));
			img_hero[1]->setPosition(Vec2(img_bg->getContentSize().width / 2, img_bg->getContentSize().height));
			img_bg->addChild(img_hero[1]);

			img_hero_info_bg[1] = ImageView::create(std::string("Fight/info_bg_") + m_to_string((*it).m_oGameAttr.m_pHero->country) + ".png");
			img_hero_info_bg[1]->setAnchorPoint(Vec2(0, 1));
			img_hero_info_bg[1]->setPosition(Vec2(0, img_hero[1]->getContentSize().height));
			img_hero[1]->addChild(img_hero_info_bg[1]);
			img_hero_info_bg[1]->setScaleX(2);
			img_hero_info_bg[1]->setScaleY(3);

			img_hero_country[1] = ImageView::create(std::string("Fight/country_zi_") + m_to_string((*it).m_oGameAttr.m_pHero->country) + ".png");
			img_hero_country[1]->setAnchorPoint(Vec2(0, 1));
			img_hero_country[1]->setPosition(Vec2(0, img_hero[1]->getContentSize().height));
			img_hero[1]->addChild(img_hero_country[1]);

			lab_hero_name[1] = Label::createWithTTF(CSGSTXT::GET(m_to_string((*it).m_oGameAttr.m_pHero->idhero).c_str()), "fonts/FZBWKSK.TTF", 36);
			lab_hero_name[1]->setTextColor(ccc4(0, 0, 0, 255));
			lab_hero_name[1]->setAnchorPoint(Vec2(0, 1));
			lab_hero_name[1]->setPosition(Vec2(10, img_hero[1]->getContentSize().height - img_hero_country[1]->getContentSize().height));
			img_hero[1]->addChild(lab_hero_name[1]);

			img_handcard_num_bg[1] = ImageView::create("Fight/handcard_bg.png");
			img_handcard_num_bg[1]->setAnchorPoint(Vec2(1, 0));
			img_handcard_num_bg[1]->setPosition(Vec2(img_hero[1]->getContentSize().width, 0));
			img_hero[1]->addChild(img_handcard_num_bg[1]);

			lab_handcard_num[1] = Label::createWithTTF("0", "fonts/FZBWKSK.TTF", 50);
			lab_handcard_num[1]->setTextColor(ccc4(0, 0, 0, 255));
			lab_handcard_num[1]->setPosition(Vec2(img_handcard_num_bg[1]->getContentSize().width / 2, img_handcard_num_bg[1]->getContentSize().height / 2));
			img_handcard_num_bg[1]->addChild(lab_handcard_num[1]);

			for (int i = 0; i < (*it).m_oGameAttr.m_pHero->blood; i++) {
				img_blood[1][i] = ImageView::create("Fight/blood_have.png");
				img_blood[1][i]->setAnchorPoint(Vec2(1, 1));
				img_blood[1][i]->setPosition(Vec2(img_hero[1]->getContentSize().width - img_blood[1][i]->getContentSize().width * 2 * i - 5, img_hero[1]->getContentSize().height - 5));
				img_hero[1]->addChild(img_blood[1][i]);
				img_blood[1][i]->setScale(2);
			}

			img_hero[1]->setScale(visibleSize.width / 8 / img_hero[1]->getContentSize().width);	//武将信息缩放到宽度1/8
			//中上方敌方武将e

			//敌方出手定时s
			Sprite* sp_pt_enemy = Sprite::create("Fight/progress_timebar.png");
			pt_1 = ProgressTimer::create(sp_pt_enemy);
			pt_1->setScaleX(img_hero[1]->getContentSize().width / pt_1->getContentSize().width);
			pt_1->setScaleY(0.2);
			pt_1->setAnchorPoint(Vec2(0, 1));
			pt_1->setPosition(Vec2(0, -10));
			img_hero[1]->addChild(pt_1);

			pt_1->setType(ProgressTimer::Type::BAR);	//条形进度条
			pt_1->setMidpoint(Vec2(0, 1));	//中心位置
			pt_1->setBarChangeRate(Vec2(1, 0));	//用作条形进度条显示的图片所占比例

			//pt_1->runAction(ProgressFromTo::create(15.0f, 100.0f, 0.0f)); //执行动画
			//敌方出手定时e

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*img_hero[1]->loadTexture(std::string("Fight/hero_big/") + m_to_string((*it).m_oGameAttr.m_pHero->idhero) + ".png");
			img_hero_info_bg[1]->loadTexture(std::string("Fight/info_bg_")+m_to_string((*it).m_oGameAttr.m_pHero->country)+".png");
			img_hero_country[1]->loadTexture(std::string("Fight/country_zi_") + m_to_string((*it).m_oGameAttr.m_pHero->country) + ".png");
			lab_hero_name[1]->setString(CSGSTXT::GET(m_to_string((*it).m_oGameAttr.m_pHero->idhero).c_str()));
			lab_handcard_num[1]->setString("0");*/
		}
	}
}

bool FightMain::onTouchHandCardBegan(Touch* touch, Event* event) {
	//被点击对象
	auto target = (ImageView*)event->getCurrentTarget();
	//将点击坐标转换到目标坐标系上去
	Vec2 touchPos = touch->getLocation();
	Vec2 locationInNode = target->convertToNodeSpace(touchPos);
	//构建一个目标对象的矩形
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	//判断点击是否发生在目标对象内
	if (rect.containsPoint(locationInNode)) {
		return true;
	}
	else {
		return false;
	}
}

void FightMain::onTouchHandCardMoved(Touch* touch, Event* event) {

}

bool FightMain::onTouchHandCardEnded(Touch* touch, Event* event) {
	Sprite* target = (Sprite*)event->getCurrentTarget();

	if (status != 0) {
		bool is_click = false;
	int i;
	for (i = 0; i < status; ++i) {
		if (i_current_card[i] == target->getTag()) {
			is_click = true;
			break;
		}
	}
	if (is_click) {	//点的牌已经被选中
		Vec2 diff = Vec2(0, -20);	//之前选中的牌向下回退
		Vec2 posSrc = sp_handcard[i_current_card[i]]->getPosition();
		Vec2 posDes = posSrc + diff;
		sp_handcard[i_current_card[i]]->setPosition(posDes);

		//前移
		//i_current_card[i] = -1;
		for (int j = i; j < status - 1; ++j) {
			i_current_card[j] = i_current_card[j + 1];
		}
		i_current_card[status - 1] = -1;
	}
	else {	//点的是未选中的牌
		bool is_full = true;
		for (i = 0; i < status; ++i) {
			if (i_current_card[i] == -1) {
				is_full = false;
				break;
			}
		}
		if (is_full) {	//如果选择的牌已经达到上限status
			Vec2 diff = Vec2(0, -20);	//之前选中的牌向下回退
			Vec2 posSrc = sp_handcard[i_current_card[0]]->getPosition();
			Vec2 posDes = posSrc + diff;
			sp_handcard[i_current_card[0]]->setPosition(posDes);

			for (int i = 0; i < status - 1; ++i) {
				i_current_card[i] = i_current_card[i + 1];
			}
			--i;
		}

		Vec2 diff = Vec2(0, 20);	//没达到上限
		Vec2 posSrc = target->getPosition();
		Vec2 posDes = posSrc + diff;
		target->setPosition(posDes);

		i_current_card[i] = target->getTag();
	}

	//for (int i = 0; i < status; ++i) {
	//	log("%d ", i_current_card[i]);
	//}
	//log("\n");
	}

	return true;
}

void FightMain::btn_confirm_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (stage == 1) {	//出牌
		Json::Value root;
		int card_i = 0;
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (it->m_nSeatId == u_player.m_nSeatId)
			{
				for (std::list<std::shared_ptr<SGSCard>>::iterator it_card = it->m_oGameAttr.m_lstPlayerCards.begin(); it_card != it->m_oGameAttr.m_lstPlayerCards.end();)
				{
					if (card_i == i_current_card[0])
					{
						root["card"] = (*it_card)->card();
						break;
					}
					else
					{
						card_i++;
						it_card++;
					}
				}
				break;
			}
		}
		std::shared_ptr<PPacket> p(new PPacket());
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			p->body = root.toStyledString();
			p->pack(GAME_OUT_CARD);
			g_lstWrite.push_back(p);
			//		this->setVisible(false);
			break;
		case ui::Widget::TouchEventType::MOVED:
			break;
		default:
			break;
		}
	}
	else if (stage == 2) {	//弃牌
		Json::Value root;
		int card_i = 0;
		for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
		{
			if (it->m_nSeatId == u_player.m_nSeatId)
			{
				for (int i = 0; i < status; ++i) {
					card_i = 0;
					for (std::list<std::shared_ptr<SGSCard>>::iterator it_card = it->m_oGameAttr.m_lstPlayerCards.begin(); it_card != it->m_oGameAttr.m_lstPlayerCards.end();)
					{
						if (card_i == i_current_card[i])
						{
							root["cards"][i] = (*it_card)->card();
							break;
						}
						else
						{
							card_i++;
							it_card++;
						}
					}
				}
				break;
			}
		}
		std::shared_ptr<PPacket> p(new PPacket());
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			p->body = root.toStyledString();
			p->pack(GAME_DISCARD);
			g_lstWrite.push_back(p);
			break;
		case ui::Widget::TouchEventType::MOVED:
			break;
		default:
			break;
		}
	}
}

void FightMain::btn_cancel_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	if (stage == 1) {	//出牌
		Json::Value root;

		std::shared_ptr<PPacket> p(new PPacket());
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			p->body = root.toStyledString();
			p->pack(GAME_CANCEL_OUT_CARD);
			g_lstWrite.push_back(p);
			//		this->setVisible(false);
			break;
		case ui::Widget::TouchEventType::MOVED:
			break;
		default:
			break;
		}
	}
	else if (stage == 2) {	//弃牌
		Json::Value root;

		std::shared_ptr<PPacket> p(new PPacket());
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			p->body = root.toStyledString();
			p->pack(GAME_CANCEL_OUT_CARD);
			g_lstWrite.push_back(p);
			//		this->setVisible(false);
			break;
		case ui::Widget::TouchEventType::MOVED:
			break;
		default:
			break;
		}
	}
}

void FightMain::UpdateHandCard() {
	for (int i = 0; i < i_current_card_num; ++i) {	//清空之前的手牌
		sp_handcard[i]->removeFromParentAndCleanup(true);
	}

	for (std::list<Player>::iterator it_p = u_room.m_lstPlayers.begin(); it_p != u_room.m_lstPlayers.end();  ++it_p) {
		if (u_player.m_nSeatId == (*it_p).m_nSeatId) {	//修改我的手牌信息
			i_current_card_num = (*it_p).m_oGameAttr.m_lstPlayerCards.size();	//现在的手牌数
			int i = 0;
			for (std::list<std::shared_ptr<SGSCard>>::iterator it_c = (*it_p).m_oGameAttr.m_lstPlayerCards.begin(); it_c != (*it_p).m_oGameAttr.m_lstPlayerCards.end(); ++i, ++it_c) {

				auto visibleSize = Director::getInstance()->getVisibleSize();
				Vec2 origin = Director::getInstance()->getVisibleOrigin();

				//////////////////////////////////
				char name[12];

				snprintf(name, 12, "%02x", (*it_c)->func());
				sp_handcard[i] = Sprite::create(std::string("Fight/card/") + name + ".png");
				sp_handcard[i]->setAnchorPoint(Vec2(0, 0));
				sp_handcard[i]->setPosition(origin.x + visibleSize.width / 4 + i * sp_handcard[i]->getContentSize().width * 0.5, origin.y);
				img_bg->addChild(sp_handcard[i]);
				sp_handcard[i]->setScale(0.5);
				//log("%s", (std::string("Fight/card/") + name + ".png").c_str());

				snprintf(name, 12, "flower_%x", (*it_c)->color());
				img_handcard_flowercolor[i] = ImageView::create(std::string("Fight/card/") + name + ".png");
				img_handcard_flowercolor[i]->setAnchorPoint(Vec2(0, 1));
				img_handcard_flowercolor[i]->setPosition(Vec2(5, sp_handcard[i]->getContentSize().height - 10));
				sp_handcard[i]->addChild(img_handcard_flowercolor[i]);
				img_handcard_flowercolor[i]->setScale(2);
				//log("%s",(std::string("Fight/card/") + name + ".png").c_str());

				int clr = (*it_c)->color();
				if (clr <= SGSCard::CARD_CLR_HEART)
				{
					snprintf(name, 12, "red_%x", (*it_c)->value());
				}
				else
				{
					snprintf(name, 12, "black_%x", (*it_c)->value());
				}

				img_handcard_num[i] = ImageView::create(std::string("Fight/card/") + name + ".png");
				img_handcard_num[i]->setAnchorPoint(Vec2(0, 1));
				img_handcard_num[i]->setPosition(Vec2(0, sp_handcard[i]->getContentSize().height - 10 - img_handcard_flowercolor[i]->getContentSize().height));
				sp_handcard[i]->addChild(img_handcard_num[i]);
				img_handcard_num[i]->setScale(2);
				//log("%s", (std::string("Fight/card/") + name + ".png").c_str());

				sp_handcard[i]->setTag(i);

				// 给背景容器添加拖拽事件s
				auto touchHandCardListener = EventListenerTouchOneByOne::create();//单指操作监听 也有多点操作
				touchHandCardListener->setSwallowTouches(true);//设置事件吞没 事件分发机制
				touchHandCardListener->onTouchBegan = CC_CALLBACK_2(FightMain::onTouchHandCardBegan, this);
				touchHandCardListener->onTouchMoved = CC_CALLBACK_2(FightMain::onTouchHandCardMoved, this);
				touchHandCardListener->onTouchEnded = CC_CALLBACK_2(FightMain::onTouchHandCardEnded, this);
				//将事件绑定到控件上
				Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchHandCardListener->clone(), sp_handcard[i]);
			}
		}
	}
	for (int i = 0; i < 20; ++i) {
		i_current_card[i] = -1;	//重置手牌全部未选中
	}
}

void FightMain::UpdateFightInfo(int i, int blood, int max_blood) {
	//更新血量
	/*int blood[2] = { 2, 1 };
	int max_blood[2] = { 4,4 };
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < blood[i]; ++j) {
			img_blood[i][j]->loadTexture("Fight/blood_have.png");
		}
		for (int j = blood[i]; j < max_blood[i]; ++j) {
			img_blood[i][j]->loadTexture("Fight/blood_lose.png");
		}
	}*/

	for (int j = 0; j < blood; ++j) {
		img_blood[i][j]->loadTexture("Fight/blood_have.png");
	}
	for (int j = blood; j < max_blood; ++j) {
		img_blood[i][j]->loadTexture("Fight/blood_lose.png");
	}
}

void FightMain::ShowMyBtnAndTimer() {
	btn_confirm->setVisible(true);
	btn_cancel->setVisible(true);

	pt_0->runAction(ProgressFromTo::create(15.0f, 100.0f, 0.0f)); //执行我的定时器
}
void FightMain::HideMyBtnAndTimer() {
	btn_confirm->setVisible(false);
	btn_cancel->setVisible(false);

	pt_0->stopAllActions(); //隐藏我的定时器
	pt_0->setPercentage(0);
}
void FightMain::ShowEnemyTimer() {
	pt_1->runAction(ProgressFromTo::create(15.0f, 100.0f, 0.0f)); //执行敌方定时器
}

void FightMain::HideEnemyTimer() {
	pt_1->stopAllActions();	//隐藏敌方定时器
	pt_1->setPercentage(0);
}

void FightMain::setStatus(int i) {
	status = i;
}

int FightMain::getStatus() {
	return status;
}

void FightMain::setStage(int i) {
	stage = i;
}

void FightMain::UpdateHandCardNum(int i, int cnt) {
	lab_handcard_num[i]->setString(m_to_string(cnt));
}

void FightMain::UpdateStageLab(std::string stage_name) {
	lab_now_stage->setString(stage_name);
}

void FightMain::Vec_create()
{
	animation_sha->setAnchorPoint(Point(0, 0));
	animation_shan->setAnchorPoint(Point(0, 0));
	animation_tao->setAnchorPoint(Point(0, 0));
	auto cache = SpriteFrameCache::getInstance();  // 创建一个缓存单例
	auto cache_1 = SpriteFrameCache::getInstance();  // 创建一个缓存单例
	auto cache_2 = SpriteFrameCache::getInstance();  // 创建一个缓存单例
	cache->addSpriteFramesWithFile("animation/TXSha/TXSha0.plist");   //通过plist配置文件添加一组精灵帧
	char name[50];
	memset(name, 0, 50);
	for (int i = 0; i < 9; i++)
	{
		sprintf(name, "sha_000%d.png", i);
		sha_vec.pushBack(cache->getSpriteFrameByName(name));
	}  //把大的图一部分一部分的切出来放进vec
	cache->addSpriteFramesWithFile("animation/TXSha/TXSha1.plist");
	sprintf(name, "sha_0009.png");
	sha_vec.pushBack(cache->getSpriteFrameByName(name));  //shan_00000.png

	cache_1->addSpriteFramesWithFile("animation/TXShan/TXShan0.plist");   //通过plist配置文件添加一组精灵帧

	memset(name, 0, 50);
	for (int i = 0; i < 9; i++)
	{
		sprintf(name, "shan_0000%d.png", i);
		shan_vec.pushBack(cache_1->getSpriteFrameByName(name));
	}  //把大的图一部分一部分的切出来放进vec


	cache_2->addSpriteFramesWithFile("animation/TXTao/TXTao0.plist");   //通过plist配置文件添加一组精灵帧

	memset(name, 0, 50);
	for (int i = 0; i < 9; i++)
	{
		sprintf(name, "tao_0000%d.png", i);
		tao_vec.pushBack(cache_2->getSpriteFrameByName(name));
	}  //把大的图一部分一部分的切出来放进vec
}

void FightMain::hid_sha(Node* sender)   //将杀的精灵隐藏
{
	animation_sha->setVisible(false);
}

void FightMain::hid_shan(Node* sender)  //将闪的精灵隐藏
{
	animation_shan->setVisible(false);
}

void FightMain::hid_tao(Node* sender)  //将桃的精灵隐藏
{
	animation_tao->setVisible(false);
}

void FightMain::show_sha(int i)
{
	//杀音效s
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sha.mp3", false);
	//杀音效e

	float x, y;
	if (0 == i)  // 0的时候自己向对面
	{
		x = win.width / 2;
		y = win.height / 5;
	}
	else
	{
		x = win.width / 2;
		y = win.height * 3.5 / 5;
	}
	animation_sha->setPosition(x, y);
	animation_sha->setVisible(true);
	auto animation = Animation::createWithSpriteFrames(sha_vec, 0.1f);  //动画的配置
	auto animate = Animate::create(animation); //包装成动作
	auto *action = Sequence::create(
		Repeat::create(animate, 1),
		CallFuncN::create(CC_CALLBACK_1(FightMain::hid_sha, this)), NULL);
	animation_sha->runAction(action);
}

void FightMain::show_shan(int i)
{
	//闪音效s
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/shan.mp3", false);

	if (0 == i)  // 0的时候自己向对面
	{
		animation_shan->setPosition(win.width / 2, win.height / 5);
	}
	else
	{
		animation_shan->setPosition(win.width / 2, win.height * 3.5 / 5);
	}
	animation_shan->setVisible(true);
	auto animation = Animation::createWithSpriteFrames(shan_vec, 0.1f);  //动画的配置
	auto animate = Animate::create(animation); //包装成动作
	auto *action = Sequence::create(
		Repeat::create(animate, 1),
		CallFuncN::create(CC_CALLBACK_1(FightMain::hid_shan, this)), NULL);
	animation_shan->runAction(action);
}

void FightMain::show_tao(int i)
{
	//桃音效s
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/tao.mp3", false);

	if (0 == i)  // 0的时候自己向对面
	{
		animation_tao->setPosition(win.width / 2, win.height / 5);
	}
	else
	{
		animation_tao->setPosition(win.width / 2, win.height * 3.5 / 5);
	}
	animation_tao->setVisible(true);
	auto animation = Animation::createWithSpriteFrames(tao_vec, 0.1f);  //动画的配置
	auto animate = Animate::create(animation); //包装成动作
	auto *action = Sequence::create(
		Repeat::create(animate, 1),
		CallFuncN::create(CC_CALLBACK_1(FightMain::hid_tao, this)), NULL);
	animation_tao->runAction(action);
}

void FightMain::GameEnd(int i) {
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it) {
		it->m_oGameAttr.m_lstPlayerCards.clear();
	}
	HideMyBtnAndTimer();		//隐藏我的按钮和定时器

	if (i == 0) {
		Layer* layer_end = FightEndWin::create();
		this->addChild(layer_end);
	}
	else if (i == 1) {
		Layer* layer_end = FightEndLose::create();
		this->addChild(layer_end);
	}
}