/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.10
Description : log
**************************************************/
#ifndef _SGS_PPACKET_H_
#define _SGS_PPACKET_H_

#include "include.h"

struct PHeader
{
	unsigned int cmd;
	unsigned int uid;
	unsigned short len;
	unsigned short svrid;

	PHeader() :cmd(0), uid(0), len(0), svrid(0) {}
	std::string& toNetStr(std::string& str);
};

class PPacket
{
	//variables
private:

protected:

public:
	PHeader header;
	std::string body;
	std::string data;

	//functions
public:
	PPacket();
	~PPacket();

	void pack(unsigned int cmd = 0, unsigned int uid = 0, unsigned short svrid = 0);
	void save(std::string str);
	int check();

protected:

private:

};


#endif // !_SGS_PPACKET_H_

