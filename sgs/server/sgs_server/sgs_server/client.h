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

class Player;

class Client
{
	/*varibles*/

private:
	Player* m_pPlayer;
protected:

public:
	static const int MAX_RECV_BUF_SIZE = 1024;
	std::list<std::shared_ptr<PPacket>> m_lstWrite;

	ev_io	m_ev_write;
	ev_io	m_ev_read;

	PPacket m_iPacket;
	std::string m_stIP;

	int m_nfd;

	char m_pRecvBuf[MAX_RECV_BUF_SIZE];

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