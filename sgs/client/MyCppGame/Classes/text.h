#ifndef SGS_TEXT_H
#define SGS_TEXT_H

#include <string>
#include "cocos2d.h"


//USING_NS_CC;

class CSGSTXT
{
public:
	static bool init;
	CSGSTXT();
	static cocos2d::ValueMap message;

	static void Init();
	static std::string GET(char* key);
	std::string operator[](char* key);
private:

};


#endif