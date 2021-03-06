#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "../Classes/model/include_all.h"

#include "Mode/SelectModeScene.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

public:
	bool onTouchHandCardBegan(Touch* touch, Event* event);		//���ƵĴ����¼�
	void onTouchHandCardMoved(Touch* touch, Event* event);
	bool onTouchHandCardEnded(Touch* touch, Event* event);

};

#endif // __HELLOWORLD_SCENE_H__
