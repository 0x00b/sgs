#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Login/LoginScene.h"
#include <memory>
// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#define MAX_RECV_BUF_SIZE 40960

std::list<std::shared_ptr<PPacket>> g_lstWrite;

int exit_all = 1;

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1334, 750);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

Player u_player;  //纪录用户信息
Room u_room;

//tcp::iostream AppDelegate::skt("10.14.115.244", "37373");
//tcp::iostream AppDelegate::skt("10.12.137.251", "37373"); 
//tcp::iostream AppDelegate::skt;


tcp::socket sock(*(new boost::asio::io_service()));
tcp::endpoint ep(boost::asio::ip::address::from_string("10.12.137.251"),37373);

void connectToSvr()
{
	try
	{
		sock.connect(ep);
	}
	catch (const std::exception&)
	{
		MessageBox("connect sever err!","");
	}
}


AppDelegate::AppDelegate() :
	th_send(AppDelegate::func_send),
	th_receive(func_receive)
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::end();
#endif

	th_send.join();
	th_receive.join();

}

void AppDelegate::func_send()
{

	while (exit_all)
	{
		if (g_lstWrite.empty()) {
			CCSleep(10);
			continue;
		}
		std::shared_ptr<PPacket>& pkt = g_lstWrite.front();
		//skt.write(pkt->data.c_str() + pkt->m_nCurLen, pkt->data.length() - pkt->m_nCurLen);
		try
		{
			sock.write_some(boost::asio::buffer(pkt->data));
		}
		catch (const std::exception&)
		{
			connectToSvr();
		}

		g_lstWrite.pop_front();

	}



	/*root[SJPROTO[E_Player]][SPlayer[EPlayer_account]] = "waterm1";
	root[SJPROTO[E_Player]][SPlayer[EPlayer_passwd]] = "123456";
	root[SJPROTO[E_Player]][SPlayer[EPlayer_name]] = "大西瓜";

	PPacket p;
	p.body = root.toStyledString();
	p.pack(1);
	s.write(p.data.c_str(), p.data.length());*/

	//Json::Value root;
	//std::string err;
	//root[SPlayer[EPlayer_account]] = "waterm1";
	//root[SPlayer[EPlayer_passwd]] = "123456";

	//std::shared_ptr<PPacket> packet(new PPacket());
	//packet->body = root.toStyledString();
	//packet->pack(1);

	////放到队列

	//g_lstWrite.push_back(packet);


	return;

}

int AppDelegate:: Do(Json::Value &pkt,int cmd)
{
	switch (cmd)
	{
	case PLAYER_LOGIN_UC:
		Do_function::PLAYER_LOGIN_UC(pkt,cmd);
		break;
	case PLAYER_CREATE_ROOM_UC:
		Do_function::PLAYER_CREATE_ROOM_UC(pkt, cmd);
		break;
	case PLAYER_ENTER_ROOM_BC:
		Do_function::PLAYER_ENTER_ROOM_BC(pkt, cmd);
		break;
	case PLAYER_QUIT_ROOM_BC:
		Do_function::PLAYER_QUIT_ROOM_BC(pkt, cmd);
		break;
	case PLAYER_READY_BC:
		Do_function::PLAYER_READY_BC(pkt, cmd);
		break;
	case PLAYER_SEARCH_ROOM_UC:
		Do_function::PLAYER_SEARCH_ROOM_UC(pkt, cmd);
		break;
	case GAME_START:
		Do_function::GAME_START(pkt, cmd);
		break;
	case GAME_SELECT_HERO_BC:
		Do_function::GAME_SELECT_HERO_BC(pkt, cmd);
		break;
	default:
		break;
	}
	return 0;
}


void AppDelegate::func_receive()
{
	PPacket pMsg;
	std::shared_ptr<char> pRecvBuf = std::shared_ptr<char>(new char[MAX_RECV_BUF_SIZE]);

	Json::Value root;
	std::string err;
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();
//	int ret_receive = 0;
	int ret_received;
	while (exit_all)
	{
		root.clear();
	//	memset(pRecvBuf, 0, MAX_RECV_BUF_SIZE);
		pMsg.body.clear();
		/* recv header*/
		//skt.read((char *)&(pMsg.header), sizeof(PHeader));
		try
		{
			sock.read_some(boost::asio::buffer(&pMsg.header,sizeof(PHeader)));
		}
		catch (const std::exception&)
		{
			connectToSvr();
		}

		pMsg.save();
		if (pMsg.header.len == 0)
		{
			pMsg.m_eStatus = STAT_END;
		}
		else if (pMsg.header.len <= MAX_RECV_BUF_SIZE)
		{
	//		ret_receive = pMsg.header.len;
			ret_received = 0;
			pMsg.m_eStatus = STAT_BODY;
			while (ret_received < pMsg.header.len)
			{
				try
				{
					ret_received +=sock.read_some(boost::asio::buffer(pRecvBuf.get()+ ret_received, pMsg.header.len-ret_received));
					//strcat(pRecvBuf, pRecvBuf2);
				}
				catch (const std::exception&)
				{
					connectToSvr();
				}
			}
			log(pRecvBuf.get());
			pMsg.body.append(pRecvBuf.get(), pMsg.header.len);
			reader->parse(pMsg.body.c_str(), pMsg.body.c_str() + pMsg.body.length(), &root, &err);
		}
		else {
			//err
		}
		//to do
		int start = time(NULL);

		if (Do(root,pMsg.header.cmd) < 0)
		{
			;
		}
		if (time(NULL) - start > 1)
		{
			//	log(FFL_s_u, "slow cmd:", self->m_iPacket.header.cmd);
		}
	}



	/*log(p.body.c_str());
	log(root["code"].asString().c_str());*/


//	log("%d", root["code"].asInt());

	delete reader;
	//MessageBox("22\n", "");
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("MyCppGame", cocos2d::Rect(0, 0, 960, 640));
#else
		glview = GLViewImpl::create("MyCppGame");
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	//director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	//director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	auto frameSize = glview->getFrameSize();
	// if the frame's height is larger than the height of medium size.
	//if (frameSize.height > mediumResolutionSize.height)
	//{
	//	director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
	//}
	//// if the frame's height is larger than the height of small size.
	//else if (frameSize.height > smallResolutionSize.height)
	//{
	//	director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	//}
	//// if the frame's height is smaller than the height of medium size.
	//else
	//{
	//	director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
	//}

	register_all_packages();

	// create a scene. it's an autorelease object
	auto scene = Login::createScene();
	// run

	director->runWithScene(scene);
	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
