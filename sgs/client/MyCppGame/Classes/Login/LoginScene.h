#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "model/include_all.h"
#include "HelloWorldScene.h"
#include "RegisterScene.h"

USING_NS_CC;
using namespace ui;

class Login : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Login);

private:
	Button* btn_login;	//µÇÂ¼
	TextField* txt_account;	//ÕËºÅ
	TextField* txt_pwd;	//ÃÜÂë
};

#endif // __LOGIN_SCENE_H__

