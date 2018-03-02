#include "text.h"

cocos2d::ValueMap CSGSTXT::message;
bool CSGSTXT::init = false;

//CSGSTXT SGSTXT;
CSGSTXT::CSGSTXT()
{
	try {
		CSGSTXT::Init();
	}
	catch (std::exception) {
		cocos2d::MessageBox("load xml fial", "");
	}
}
void CSGSTXT::Init()
{
	//中文显示s
	//过时
	//Dictionary* message = Dictionary::createWithContentsOfFile("fonts/ChineseStrings.xml");
	//auto sixmodeValue = message->valueForKey("sixmode");    //根据key，获取value
	//const char* sixmodeString = sixmodeValue->getCString();    //将value转化为字符串
	//替代
	message = cocos2d::FileUtils::getInstance()->getValueMapFromFile("fonts/ChineseStrings.xml");
}
std::string CSGSTXT::operator[](char* key)
{
	return  message[key].asString();
}
std::string CSGSTXT::GET(char* key)
{
	if (!init)
	{
		CSGSTXT::Init();
		init = true;
	}
	return  message[key].asString();
}