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
	//������ʾs
	//��ʱ
	//Dictionary* message = Dictionary::createWithContentsOfFile("fonts/ChineseStrings.xml");
	//auto sixmodeValue = message->valueForKey("sixmode");    //����key����ȡvalue
	//const char* sixmodeString = sixmodeValue->getCString();    //��valueת��Ϊ�ַ���
	//���
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