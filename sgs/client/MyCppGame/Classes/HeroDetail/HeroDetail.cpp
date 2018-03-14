#include "HeroDetail.h"
#include <string>
#include "../Classes/Mode/SelectModeScene.h"

USING_NS_CC;

Scene* HeroDetail::createScene()
{
	return HeroDetail::create();
}

bool HeroDetail::init()
{
	//////////////////////////////
	if (!Scene::init())
	{
		return false;
	}
	win = Director::getInstance()->getVisibleSize();
	int i;
	for (i = 0; i < 4; i++)
	{
		country[i] = Layer::create();
	}
	i_check = 0;
	Sprite *backGround = Sprite::create("res/model_select_bg.png");
	backGround->setPosition(0, 0);
	backGround->setAnchorPoint(Point(0, 0));
	Size mywinsize = Director::getInstance()->getWinSize();
	win = mywinsize;
	float winw = mywinsize.width; //获取屏幕宽度
	float winh = mywinsize.height;//获取屏幕高度
	float spx = backGround->getContentSize().width;
	float spy = backGround->getContentSize().height;
	backGround->setScaleX(winw / spx); //设置精灵宽度缩放比例
	backGround->setScaleY(winh / spy);
	this->addChild(backGround);
	pic = Sprite::create();
	pic->setAnchorPoint(Point(0, 0));
	pic->setPosition(win.width*0.16, win.height*0.1);
	addChild(pic);
	int n;
	for (n = 0; n < 2; n++)
	{
		skill[n] = Label::create("","",18);
		skill[n]->setAnchorPoint(Point(0, 0));
		skill[n]->setPosition(Point(win.width*0.5, (0.6+ (3 - n)*0.05)*win.height));
		skill[n]->setColor(Color3B(0, 0, 0));
//		skill[n]->setMaxLineWidth(1);
		skill[n]->setDimensions(560,60);
		skill[n]->setLineBreakWithoutSpace(true);
		addChild(skill[n]);
	}
	for (n = 2; n < 4; n++)
	{
		skill[n] = Label::create("", "", 18);
		skill[n]->setAnchorPoint(Point(0, 0));
		skill[n]->setPosition(Point(win.width*0.5, (0.43 + (3 - n)*0.05)*win.height));
		skill[n]->setColor(Color3B(0, 0, 0));
		skill[n]->setDimensions(560, 60);
		addChild(skill[n]);
	}
	for (n = 4; n < 6; n++)
	{
		skill[n] = Label::create("", "", 18);
		skill[n]->setAnchorPoint(Point(0, 0));
		skill[n]->setPosition(Point(win.width*0.5, (0.43 + (5 - n)*0.05)*win.height));
		skill[n]->setColor(Color3B(0, 0, 0));
		skill[n]->setDimensions(560, 60);
		addChild(skill[n]);
	}
	//0.35   0.12
	btn_back = cocos2d::ui::Button::create("Bg/back_bg.png");
	btn_back->setAnchorPoint(Vec2(0, 1));
	btn_back->setPosition(Vec2(0, win.height ));
	addChild(btn_back);
	btn_back->addTouchEventListener(CC_CALLBACK_2(HeroDetail::DidBack, this));

	//init_detail();
	init_country_layer();  // 层创建好之后对他们进来初始化
	for (i = 0; i < 4; i++)
	{
		addChild(country[i]);  //把4个层加进来
	}
	country[0]->setVisible(true);
	country[1]->setVisible(false);  //默认显示第一个，别的先隐藏。
	country[2]->setVisible(false);
	country[3]->setVisible(false);
	select_country_btn();  //把几个选择按钮加进来
	return true;
}

HeroDetail::HeroDetail()
{
}


HeroDetail::~HeroDetail()
{
}

void HeroDetail::select_country_btn()
{
	int i, j;

	char name_pic[50];
	char name2_pic[50];

	for (i = 0; i < 4; i++)
	{
		sprintf(name_pic, "Fight/country_zi_%d.png", i + 1);  //   \\转义
		sprintf(name2_pic, "Fight/country_zi_%d.png", i + 1);
		button_select_country[i] = cocos2d::ui::Button::create(name_pic, name2_pic, name_pic);
		button_select_country[i]->setTag(i+100);
		country_size[i] = button_select_country[i]->getCustomSize();
	}

	for (i = 0; i < 4; i++)
	{
		country_scale_x[i] = win.width / 8 / country_size[i].width;
		country_scale_y[i] = win.height / 10 / country_size[i].height;
	/*	button_select_country[i]->setScaleX(country_scale_x[i]);
		button_select_country[i]->setScaleY(country_scale_y[i]);*/
		button_select_country[i]->setScale(country_scale_y[i]);
		button_select_country[i]->setAnchorPoint(Point(0, 0));
		button_select_country[i]->addTouchEventListener(CC_CALLBACK_2(HeroDetail::select_country, this));
	}

	for (i = 0; i < 4; i++)
	{
		position[i].x = win.width*0.02;
		position[i].y = win.height*(0.4+(3-i)*0.1);
		button_select_country[i]->setPosition(position[i]);
		addChild(button_select_country[i]);
	}
}

void HeroDetail::init_detail()
{
	//ifstream myfile("res/HeroDetail.txt");
	//string temp;
	//if (!myfile.is_open())
	//{
	////	cout << "未成功打开文件" << endl;
	////	log("123123123\n");T.RCE
	//}
//	auto fu = FileUtils::getInstance();
//	/*log("aaaaaaaa");
//	log("%s", fu->getWritablePath().c_str());*/
//	Data d = fu->getDataFromFile(fu->fullPathFromRelativeFile("HeroDetail.txt", fu->getWritablePath()));
//	//log("%s", d.getBytes());
//	int i=0;
//	int j;
//	Hero new_hero;
//	int aaa;
//	char * a = (char *)d.getBytes();
//	char * p;
//	const char * split = "#"; //
//	p = strtok(a,split);
//	aaa = 16;
//	p = strtok(NULL, split);
//	////MessageBox("2", "123");
//	while (i<aaa) {
//
//
////		new_hero.idhero = atol(p);
//		new_hero.idhero = 1;
//		//getline(myfile, temp);
//		p = strtok(NULL, split);
//		new_hero.name = p;
//		p = strtok(NULL, split);
//	//	new_hero.country = atol(p);
//		new_hero.country = 1;
//		p = strtok(NULL, split);
//		new_hero.skill_1_name = p;
//		p = strtok(NULL, split);
//		new_hero.skill_1_intro = p;
//		p = strtok(NULL, split);
//		new_hero.skill_2_name = p;
//		p = strtok(NULL, split);
//		new_hero.skill_2_intro = p;
//		p = strtok(NULL, split);
//		new_hero.master_skill_name = p;
//		p = strtok(NULL, split);
//		new_hero.master_skill_intro = p;
//		p = strtok(NULL, split);
//		hero_detail.push_back(new_hero);
//		i++;
//	}
	/*while (getline(myfile, temp))
	{
		new_hero.idhero = strtol(temp.c_str(), NULL, 0);
		getline(myfile, temp);
		new_hero.name = temp;
		getline(myfile, temp);
		new_hero.country = strtol(temp.c_str(), NULL, 0);
		getline(myfile, temp);
		new_hero.skill_1_name = temp;
		getline(myfile, temp);
		new_hero.skill_1_intro = temp;
		getline(myfile, temp);
		new_hero.skill_2_name = temp;
		getline(myfile, temp);
		new_hero.skill_2_intro = temp;
		getline(myfile, temp);
		new_hero.master_skill_name = temp;
		getline(myfile, temp);
		new_hero.master_skill_intro = temp;
		getline(myfile, temp);
		hero_detail.push_back(new_hero);
		i++;
	}*/;
	//myfile.close();
}

void HeroDetail::init_country_layer()  //初始化4个层
{
	int i = u_room.hero_all_detail.size();
	int j;
	char name_pic[50];
	float scalex, scaley;
	for (j = 0; j < 4; j++)
	{
		num_country[j] = 0;
	}
	for (j = 0; j < i; j++)
	{
		sprintf(name_pic, "SelectHero2/%d.png", u_room.hero_all_detail[j].idhero);
		cocos2d::ui::Button * btn_tim = cocos2d::ui::Button::create(name_pic, name_pic, name_pic);
		btn_tim->setAnchorPoint(Point(0, 0));
		btn_tim->setPosition(Point(win.width / 6.5 + num_country[u_room.hero_all_detail[j].country-1] % 5 * (win.width*0.15), win.height/8+ (1-num_country[u_room.hero_all_detail[j].country - 1] / 5) * (win.height / 2.6)));
		Size a = btn_tim->getContentSize();
		scalex = win.width / 7.5 / a.width;
		scaley = win.height / 3 / a.height;
		btn_tim->setScaleX(scalex);
		btn_tim->setScaleY(scaley);
		btn_tim->setTag(j);
		all_hero.push_back(btn_tim);
		btn_tim->addTouchEventListener(CC_CALLBACK_2(HeroDetail::Selet_Detail_Hero, this));
		country[u_room.hero_all_detail[j].country - 1]->addChild(btn_tim);
		num_country[u_room.hero_all_detail[j].country - 1]++;
	}
}

void HeroDetail::select_country(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{	
	int a = ((cocos2d::ui::Button*)sender)->getTag()-100;
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		switch (a)
		{
		case 0:country;
			country[0]->setVisible(true);
			country[1]->setVisible(false);
			country[2]->setVisible(false);
			country[3]->setVisible(false);
			break;  //魏
		case 1:
			country[0]->setVisible(false);
			country[1]->setVisible(true);
			country[2]->setVisible(false);
			country[3]->setVisible(false);
			; break;
		case 2:
			country[0]->setVisible(false);
			country[1]->setVisible(false);
			country[2]->setVisible(true);
			country[3]->setVisible(false);
			; break;
		case 3:
			country[0]->setVisible(false);
			country[1]->setVisible(false);
			country[2]->setVisible(false);
			country[3]->setVisible(true);
			; break;
		}
		;
		for (int i = 0; i < 6; i++)
		{
			skill[i]->setVisible(false);
		}
		pic->setVisible(false);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
	i_check = 0;
}

void HeroDetail::DidBack(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (i_check == 0)
		{	
			Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5f, HelloWorld::createScene()));
		}
		else
		{
			Director::getInstance()->replaceScene(HeroDetail::createScene());
		}
		break;
	}
}


void HeroDetail::Selet_Detail_Hero(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	int a = ((cocos2d::ui::Button*)sender)->getTag();
	int i;
	char name_pic[50];
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
	/*	skill[0]->setString(hero_detail[a].skill_1_name.c_str());
		skill[1]->setString(hero_detail[a].skill_1_intro.c_str());
		skill[2]->setString(hero_detail[a].skill_2_name.c_str());
		skill[3]->setString(hero_detail[a].skill_2_intro.c_str());*/
		for (i = 0; i < 4; i++)
		{
			country[i]->setVisible(false);
		}
		for (i = 0; i < 6; i++)
		{
			skill[i]->setVisible(true);
		}
		pic->setVisible(true);
		skill[0]->setString(u_room.hero_all_detail[a].skill_1_name);
		skill[1]->setString(u_room.hero_all_detail[a].skill_1_intro);
		skill[2]->setString(u_room.hero_all_detail[a].skill_2_name);
		skill[3]->setString(u_room.hero_all_detail[a].skill_2_intro);
		skill[4]->setString(u_room.hero_all_detail[a].master_skill_name);
		skill[5]->setString(u_room.hero_all_detail[a].master_skill_intro);
		sprintf(name_pic, "SelectHero2/%d.png", u_room.hero_all_detail[a].idhero);
		pic->setTexture(name_pic);
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
	i_check = 1;
}