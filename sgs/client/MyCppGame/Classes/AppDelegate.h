#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include <iostream>
#include <string>

#include "boost/asio.hpp"
#include "ppacket.h"

#include "./Classes/jsonproto/jsonproto.h"
#include "./Classes/libs/json/json.h"
#include "./Classes/libs/json/json-forwards.h"

using boost::asio::ip::tcp;

#ifdef WIN32  
#define CCSleep(t)  Sleep(t)  
#elif defined (IOS || ANDROID)  
#define CCSleep(t)  USleep(t)  
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

