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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...
	// 3. add your codes below...
	//������s
	Layer* layer_bg = Layer::create();
	this->addChild(layer_bg);
	//������e

	//����ͼs
	img_bg = ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer_bg->addChild(img_bg);
	//����ͼe

	i_current_card_num = 0;	//��ʼ��������Ϊ0

	selectHero = SelectHero2Layer::create();
	this->addChild(selectHero,2,"selectHero");

	return true;
}

void FightMain::InitHeroInfo() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ�������佫��Ϣ
	int i = 0;
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); i++,++it)
	{
		if (u_player.m_nSeatId == (*it).m_nSeatId) {
			//���½��ҷ��佫s
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

			img_hero[0]->setScale(visibleSize.width / 8 / img_hero[0]->getContentSize().width);	//�佫��Ϣ���ŵ����1/8
			//���½��ҷ��佫e

			//�ҷ����ֶ�ʱs
			Sprite* sp_pt_my = Sprite::create("Fight/progress_timebar.png");
			pt_0 = ProgressTimer::create(sp_pt_my);
			pt_0->setScaleX(visibleSize.width / 2 / pt_0->getContentSize().width);
			pt_0->setScaleY(0.1);
			pt_0->setAnchorPoint(Vec2(0.5, 0.5));
			pt_0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.3));
			img_bg->addChild(pt_0);

			pt_0->setType(ProgressTimer::Type::BAR);	//���ν�����
			pt_0->setMidpoint(Vec2(0, 1));	//����λ��
			pt_0->setBarChangeRate(Vec2(1, 0));	//�������ν�������ʾ��ͼƬ��ռ����

			pt_0->runAction(ProgressFromTo::create(15.0f, 100.0f, 0.0f)); //ִ�ж���
			//�ҷ����ֶ�ʱe

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*img_hero[0]->loadTexture(std::string("Fight/hero_big/") + m_to_string((*it).m_oGameAttr.m_pHero->idhero) + ".png");
			img_hero_info_bg[0]->loadTexture(std::string("Fight/info_bg_")+m_to_string((*it).m_oGameAttr.m_pHero->country)+".png");
			img_hero_country[0]->loadTexture(std::string("Fight/country_zi_") + m_to_string((*it).m_oGameAttr.m_pHero->country) + ".png");
			lab_hero_name[0]->setString(CSGSTXT::GET(m_to_string((*it).m_oGameAttr.m_pHero->idhero).c_str()));
			lab_handcard_num[0]->setString("0");*/

			//ѡ������ʱ��ȷ�� ȡ����ťs
			btn_confirm = Button::create("Bg/btn_bg.png");
			btn_confirm->setPosition(pt_0->getPosition() - Vec2(btn_confirm->getContentSize().width * 1.5, 30));
			img_bg->addChild(btn_confirm);

			Label* lab_confirm = Label::createWithTTF(CSGSTXT::GET("confirm"), "fonts/FZBWKSK.TTF", 36);
			lab_confirm->setPosition(pt_0->getPosition() - Vec2(btn_confirm->getContentSize().width * 1.5, 30));
			img_bg->addChild(lab_confirm);

			Button* btn_cancel = Button::create("Bg/btn_bg.png");
			btn_cancel->setPosition(pt_0->getPosition() - Vec2(-btn_confirm->getContentSize().width * 1.5, 30));
			img_bg->addChild(btn_cancel);

			Label* lab_cancel = Label::createWithTTF(CSGSTXT::GET("cancel"), "fonts/FZBWKSK.TTF", 36);
			lab_cancel->setPosition(pt_0->getPosition() - Vec2(-btn_confirm->getContentSize().width * 1.5, 30));
			img_bg->addChild(lab_cancel);

			btn_confirm->addTouchEventListener(CC_CALLBACK_2(FightMain::btn_confirm_card, this));
			//ѡ������ʱ��ȷ�� ȡ����ťe
		}
		else {
			//���Ϸ��з��佫s
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

			img_hero[1]->setScale(visibleSize.width / 8 / img_hero[1]->getContentSize().width);	//�佫��Ϣ���ŵ����1/8
			//���Ϸ��з��佫e

			//�з����ֶ�ʱs
			Sprite* sp_pt_enemy = Sprite::create("Fight/progress_timebar.png");
			pt_1 = ProgressTimer::create(sp_pt_enemy);
			pt_1->setScaleX(img_hero[1]->getContentSize().width / pt_1->getContentSize().width);
			pt_1->setScaleY(0.2);
			pt_1->setAnchorPoint(Vec2(0, 1));
			pt_1->setPosition(Vec2(0, -10));
			img_hero[1]->addChild(pt_1);

			pt_1->setType(ProgressTimer::Type::BAR);	//���ν�����
			pt_1->setMidpoint(Vec2(0, 1));	//����λ��
			pt_1->setBarChangeRate(Vec2(1, 0));	//�������ν�������ʾ��ͼƬ��ռ����

			pt_1->runAction(ProgressFromTo::create(15.0f, 100.0f, 0.0f)); //ִ�ж���
			//�з����ֶ�ʱe

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

void FightMain::onTouchHandCardMoved(Touch* touch, Event* event) {

}

bool FightMain::onTouchHandCardEnded(Touch* touch, Event* event) {
	Sprite* target = (Sprite*)event->getCurrentTarget();

	if (i_current_card == target->getTag()) {	//������Ѿ���ѡ��
		Vec2 diff = Vec2(0, -20);	//֮ǰѡ�е������»���
		Vec2 posSrc = sp_handcard[i_current_card]->getPosition();
		Vec2 posDes = posSrc + diff;
		sp_handcard[i_current_card]->setPosition(posDes);
		i_current_card = -1;
	}
	else {	//�����δѡ�е���
		if (i_current_card != -1) {	//���֮ǰ���Ʊ�ѡ��
			Vec2 diff = Vec2(0, -20);	//֮ǰѡ�е������»���
			Vec2 posSrc = sp_handcard[i_current_card]->getPosition();
			Vec2 posDes = posSrc + diff;
			sp_handcard[i_current_card]->setPosition(posDes);
		}

		Vec2 diff = Vec2(0, 20);	//ѡ�е�������ͻ��
		Vec2 posSrc = target->getPosition();
		Vec2 posDes = posSrc + diff;
		target->setPosition(posDes);

		i_current_card = target->getTag();
	}

	return true;
}

void FightMain::btn_confirm_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	Json::Value root;
	int card_i = 0;
	for (std::list<Player>::iterator it = u_room.m_lstPlayers.begin(); it != u_room.m_lstPlayers.end(); ++it)
	{
		if (it->m_nSeatId == u_player.m_nSeatId)
		{
			for (std::list<std::shared_ptr<SGSCard>>::iterator it_card = it->m_oGameAttr.m_lstPlayerCards.begin(); it_card != it->m_oGameAttr.m_lstPlayerCards.end();)
			{
				if (card_i == i_current_card)
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

void FightMain::UpdateHandCard() {
	for (int i = 0; i < i_current_card_num; ++i) {	//���֮ǰ������
		sp_handcard[i]->removeFromParentAndCleanup(true);
	}

	for (std::list<Player>::iterator it_p = u_room.m_lstPlayers.begin(); it_p != u_room.m_lstPlayers.end();  ++it_p) {
		if (u_player.m_nSeatId == (*it_p).m_nSeatId) {
			i_current_card_num = (*it_p).m_oGameAttr.m_lstPlayerCards.size();	//���ڵ�������
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
				log("%s", (std::string("Fight/card/") + name + ".png").c_str());

				snprintf(name, 12, "flower_%x", (*it_c)->color());
				img_handcard_flowercolor[i] = ImageView::create(std::string("Fight/card/") + name + ".png");
				img_handcard_flowercolor[i]->setAnchorPoint(Vec2(0, 1));
				img_handcard_flowercolor[i]->setPosition(Vec2(5, sp_handcard[i]->getContentSize().height - 10));
				sp_handcard[i]->addChild(img_handcard_flowercolor[i]);
				img_handcard_flowercolor[i]->setScale(2);
				log("%s",(std::string("Fight/card/") + name + ".png").c_str());

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
				log("%s", (std::string("Fight/card/") + name + ".png").c_str());

				sp_handcard[i]->setTag(i);

				// ���������������ק�¼�s
				auto touchHandCardListener = EventListenerTouchOneByOne::create();//��ָ�������� Ҳ�ж�����
				touchHandCardListener->setSwallowTouches(true);//�����¼���û �¼��ַ�����
				touchHandCardListener->onTouchBegan = CC_CALLBACK_2(FightMain::onTouchHandCardBegan, this);
				touchHandCardListener->onTouchMoved = CC_CALLBACK_2(FightMain::onTouchHandCardMoved, this);
				touchHandCardListener->onTouchEnded = CC_CALLBACK_2(FightMain::onTouchHandCardEnded, this);
				//���¼��󶨵��ؼ���
				Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchHandCardListener->clone(), sp_handcard[i]);
			}
		}
	}
	i_current_card = -1;	//��������ȫ��δѡ��
}