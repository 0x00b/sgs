#ifndef __SEARCHHOME_LAYER_H__
#define __SEARCHHOME_LAYER_H__

#include "../Classes/model/include_all.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace ui;

class SearchHome : public cocos2d::Layer
{
public:

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(SearchHome);
private:
	ImageView* img_bg;
	Button* btn_startsearch;		//搜索按钮
private:
	void closeAnimation(Node* pSender);	//执行动画后关闭层
};

#endif // __SEARCHHOME_LAYER_H__
