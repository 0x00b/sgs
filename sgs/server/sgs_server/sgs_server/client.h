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
#include "player.h"

class Client
{
	/*varibles*/

private:
	Player* m_pPlayer;
protected:

public:
	ev_io	m_ev_write;
	ev_io	m_ev_read;

	PPacket m_iPacket;
	std::string m_stIP;

	int m_nfd;

	/*functions*/
public:
	Client(Player* p);
	~Client();

	int Active();

	static void Read_cb(struct ev_loop* loop, ev_io* w, int revents);
	static void Write_cb(struct ev_loop* loop, ev_io* w, int revents);


protected:

private:

};

#endif // ! _SGS_CLIENT_H_