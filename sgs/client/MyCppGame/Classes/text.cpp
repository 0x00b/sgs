#include "text.h"


cocos2d::ValueMap CSGSTXT::message;

CSGSTXT SGSTXT;
CSGSTXT::CSGSTXT()
{
	CSGSTXT::Init();
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