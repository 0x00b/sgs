#ifndef __FightEndLose_LAYER_H__
#define __FightEndLose_LAYER_H__

#include "model/include_all.h"

USING_NS_CC;
using namespace ui;

class FightEndLose : public cocos2d::Layer
{
public:

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(FightEndLose);
private:
	ImageView* img_bg;	//����
private:
	void BackToHome(float ft);	//��ʱִ�еĻص����䳡���ĺ���
};

#endif // __FightEndLose_LAYER_H__