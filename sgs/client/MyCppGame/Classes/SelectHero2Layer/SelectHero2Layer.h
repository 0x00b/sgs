#pragma once

#include "../Classes/model/include_all.h"

using namespace std;

USING_NS_CC;

class SelectHero2Layer :public Layer
{
public:
	SelectHero2Layer();
	~SelectHero2Layer();

	virtual bool init();

	void update(float dt);

	void setProgressTime(CCProgressTimer **progresstime1);

	void ShowHero(int hero[10]);

	CREATE_FUNC(SelectHero2Layer);
private:
	Size win;

	cocos2d::CCProgressTimer *progresstime1;

	cocos2d::ui::Button*  button_hero[10];  //10���佫

	Point position[10]; //10���佫λ��
	Size size_hero[10];  //10��ͼ��С
	float scale_x[10];  //10��ͼX����
	float scale_y[10];  //10��ͼY����
		

};

