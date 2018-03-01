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
	Button* btn_startsearch;		//������ť
	TextField* txt_homeid;	//����
private:
	void closeAnimation(Node* pSender);	//ִ�ж�����رղ�
};

#endif // __SEARCHHOME_LAYER_H__
