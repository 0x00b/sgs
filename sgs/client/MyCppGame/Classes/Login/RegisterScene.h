#ifndef __REGISTER_SCENE_H__
#define __REGISTER_SCENE_H__

#include "model/include_all.h"
#include "LoginScene.h"

USING_NS_CC;
using namespace ui;

class Register : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Register);

private:
	Button* btn_register;	//◊¢≤·
	TextField* txt_account;	//’À∫≈
	TextField* txt_pwd;	//√‹¬Î
	TextField* txt_pwd_again;	//√‹¬Î÷ÿ∏¥
};

#endif // __REGISTER_SCENE_H__

