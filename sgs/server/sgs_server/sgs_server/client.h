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
	PPacket m_iPacket;
	int m_nfd;
protected:

public:

	/*functions*/
public:
	Client();
	~Client();

protected:

private:

};

#endif // ! _SGS_CLIENT_H_