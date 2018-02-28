#ifndef SGS_TEXT_H
#define SGS_TEXT_H

#include <string>
#include "cocos2d.h"


//USING_NS_CC;

class CSGSTXT
{
public:
	CSGSTXT();
	static cocos2d::ValueMap message;

	static void Init();
	std::string operator[](char* key);
private:

} ;
 

#endif