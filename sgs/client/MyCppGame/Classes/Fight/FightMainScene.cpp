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
	ImageView* img_bg = ImageView::create("Bg/scene_bg.png");
	img_bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer_bg->addChild(img_bg);
	//����ͼe

	//���½��ҷ��佫s
	img_hero[0] = ImageView::create("Fight/hero_big/liubei.png");
	img_hero[0]->setAnchorPoint(Vec2(1, 0));
	img_hero[0]->setPosition(Vec2(img_bg->getContentSize().width, 0));
	img_bg->addChild(img_hero[0]);

	img_hero_info_bg[0] = ImageView::create("Fight/shu.png");
	img_hero_info_bg[0]->setAnchorPoint(Vec2(0, 1));
	img_hero_info_bg[0]->setPosition(Vec2(0, img_hero[0]->getContentSize().height));
	img_hero[0]->addChild(img_hero_info_bg[0]);
	img_hero_info_bg[0]->setScaleX(2);
	img_hero_info_bg[0]->setScaleY(3);

	img_hero_country[0] = ImageView::create("Fight/SHUZI.png");
	img_hero_country[0]->setAnchorPoint(Vec2(0, 1));
	img_hero_country[0]->setPosition(Vec2(0, img_hero[0]->getContentSize().height));
	img_hero[0]->addChild(img_hero_country[0]);

	lab_hero_name[0] = Label::createWithTTF(CSGSTXT::GET("liubei"), "fonts/FZBWKSK.TTF", 36);
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
										//Vec2(x,y)����ʾ��Ȼ��� x ������ͼƬ��δ��ʾ���߶Ȼ��� y ������ͼƬ��δ��ʾ��������ʾ��������

	pt_0->runAction(ProgressFromTo::create(15.0f, 100.0f, 0.0f)); //ִ�ж���
																  //�ҷ����ֶ�ʱe

																  //���Ϸ��з��佫s
	img_hero[1] = ImageView::create("Fight/hero_big/sunshangxiang.png");
	img_hero[1]->setAnchorPoint(Vec2(0.5, 1));
	img_hero[1]->setPosition(Vec2(img_bg->getContentSize().width / 2, img_bg->getContentSize().height));
	img_bg->addChild(img_hero[1]);

	img_hero_info_bg[1] = ImageView::create("Fight/wu.png");
	img_hero_info_bg[1]->setAnchorPoint(Vec2(0, 1));
	img_hero_info_bg[1]->setPosition(Vec2(0, img_hero[0]->getContentSize().height));
	img_hero[1]->addChild(img_hero_info_bg[1]);
	img_hero_info_bg[1]->setScaleX(2);
	img_hero_info_bg[1]->setScaleY(3);

	img_hero_country[1] = ImageView::create("Fight/WUZI.png");
	img_hero_country[1]->setAnchorPoint(Vec2(0, 1));
	img_hero_country[1]->setPosition(Vec2(0, img_hero[1]->getContentSize().height));
	img_hero[1]->addChild(img_hero_country[1]);

	lab_hero_name[1] = Label::createWithTTF(CSGSTXT::GET("sunshangxiang"), "fonts/FZBWKSK.TTF", 36);
	lab_hero_name[1]->setTextColor(ccc4(0, 0, 0, 255));
	lab_hero_name[1]->setAnchorPoint(Vec2(0, 1));
	lab_hero_name[1]->setPosition(Vec2(10, img_hero[1]->getContentSize().height - img_hero_country[1]->getContentSize().height));
	img_hero[1]->addChild(lab_hero_name[1]);

	img_handcard_num_bg[1] = ImageView::create("Fight/handcard_bg.png");
	img_handcard_num_bg[1]->setAnchorPoint(Vec2(1, 0));
	img_handcard_num_bg[1]->setPosition(Vec2(img_hero[0]->getContentSize().width, 0));
	img_hero[1]->addChild(img_handcard_num_bg[1]);

	lab_handcard_num[1] = Label::createWithTTF("0", "fonts/FZBWKSK.TTF", 50);
	lab_handcard_num[1]->setTextColor(ccc4(0, 0, 0, 255));
	lab_handcard_num[1]->setPosition(Vec2(img_handcard_num_bg[1]->getContentSize().width / 2, img_handcard_num_bg[1]->getContentSize().height / 2));
	img_handcard_num_bg[1]->addChild(lab_handcard_num[1]);

	img_hero[1]->setScale(visibleSize.width / 8 / img_hero[1]->getContentSize().width);	//�佫��Ϣ���ŵ����1/8
																						//���Ϸ��з��佫e

																						//�з����ֶ�ʱs
	Sprite* sp_pt_enemy = Sprite::create("Fight/progress_timebar.png");
	pt_1 = ProgressTimer::create(sp_pt_enemy);
	pt_1->setScaleX(img_hero[1]->getContentSize().width / pt_1->getContentSize().width);
	pt_1->setScaleY(0.2);
	pt_1->setAnchorPoint(Vec2(0, 1));
	pt_1->setPosition(Vec2(0, -1));
	img_hero[1]->addChild(pt_1);

	pt_1->setType(ProgressTimer::Type::BAR);	//���ν�����
	pt_1->setMidpoint(Vec2(0, 1));	//����λ��
	pt_1->setBarChangeRate(Vec2(1, 0));	//�������ν�������ʾ��ͼƬ��ռ����
										//Vec2(x,y)����ʾ��Ȼ��� x ������ͼƬ��δ��ʾ���߶Ȼ��� y ������ͼƬ��δ��ʾ��������ʾ��������

	ProgressFromTo* to1 = ProgressFromTo::create(15.0f, 100.0f, 0.0f);	//����������	����ʱ��15��
	pt_1->runAction(to1); //ִ�ж���
						  //�з����ֶ�ʱe

						  //�ҷ�����s
	Sprite* sp_handcard[20];
	for (int i = 0; i < 5; i++) {
		sp_handcard[i] = Sprite::create("Fight/card/baguazhen.png");
		sp_handcard[i]->setAnchorPoint(Vec2(0, 0));
		sp_handcard[i]->setPosition(origin.x + visibleSize.width / 4 + i * sp_handcard[i]->getContentSize().width * 0.5, origin.y);
		img_bg->addChild(sp_handcard[i]);
		sp_handcard[i]->setScale(0.5);
	}
	//�ҷ�����e

	//ѡ������ʱ��ȷ�� ȡ����ťs
	Button* btn_confirm = Button::create("Bg/btn_bg.png");
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
	//ѡ������ʱ��ȷ�� ȡ����ťe

	selectHero = SelectHero2Layer::create();
	this->addChild(selectHero,2,"selectHero");

	return true;
}

void FightMain::UpdateHeroInfo() {
	//���õ����佫��Ϣ
	img_hero[0]->loadTexture("Fight/hero_big/sunquan.png");
	img_hero_info_bg[0]->loadTexture("Fight/wu.png");
	img_hero_country[0]->loadTexture("Fight/WUZI.png");
	lab_hero_name[0]->setString(CSGSTXT::GET("sunquan"));
	lab_handcard_num[0]->setString("4");

	img_hero[1]->loadTexture("Fight/hero_big/caocao.png");
	img_hero_info_bg[1]->loadTexture("Fight/wei.png");
	img_hero_country[1]->loadTexture("Fight/WEIZI.png");
	lab_hero_name[1]->setString(CSGSTXT::GET("caocao"));
	lab_handcard_num[1]->setString("4");
}