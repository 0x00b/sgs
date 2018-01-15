/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description :
**************************************************/
#ifndef _SGS_CLIENT_H_
#define _SGS_CLIENT_H_

#include "include.h"
#include "ppacket.h"

class Client
{
	/*varibles*/

private:
protected:

public:
	PPacket m_iPacket;
	std::string m_stIP;
	int m_nfd;

	/*functions*/
public:
	Client();
	~Client();

protected:

private:

};

#endif // ! _SGS_CLIENT_H_