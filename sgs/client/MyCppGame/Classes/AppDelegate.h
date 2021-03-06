#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "../Classes/model/include_all.h"
#include "Do_function.h"
#include "../Classes/HeroDetail/HeroDetail.h"
using boost::asio::ip::tcp;

#ifdef WIN32  
#define CCSleep(t)  Sleep(t)  
#else
#define CCSleep(t)  sleep(t)  
#endif  


/**
@brief    The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

public:
	//static tcp::iostream skt;
	std::thread th_send;
	std::thread th_receive;

	static void func_send();
	static void func_receive();

	static int Do(Json::Value &pkt,int cmd);

};

#endif // _APP_DELEGATE_H_

