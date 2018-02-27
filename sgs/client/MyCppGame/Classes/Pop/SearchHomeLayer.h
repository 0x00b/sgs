#ifndef __SEARCHHOME_LAYER_H__
#define __SEARCHHOME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui\CocosGUI.h"
#include "ui\UIWidget.h"

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
};

#endif // __SEARCHHOME_LAYER_H__
