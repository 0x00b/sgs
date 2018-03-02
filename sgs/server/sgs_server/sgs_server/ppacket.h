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

enum PKT_STATUS
{
	STAT_HEADER = 1,
	STAT_BODY,
	STAT_END,
};

class Packet
{
	//variables
private:

protected:

public:

	PHeader header;
	std::string body;
	std::string data;

	PKT_STATUS m_eStatus;

	//functions
public:
	Packet();
	~Packet();

protected:

private:

};

class PPacket
{
public:
	explicit PPacket();
	explicit PPacket(std::shared_ptr<Packet>& pkt);
	explicit PPacket(const PPacket& pkt);

	void pack(unsigned int cmd = 0, unsigned int uid = 0, unsigned short svrid = 0);
	void pack(unsigned int cmd, std::string &body_, unsigned int uid = 0, unsigned short svrid = 0);
	int save();
	int check();

	inline PHeader& header();
	inline std::string& body();
	inline std::string& body(std::string& str);
	inline std::string& data();
	inline PKT_STATUS& status();
	inline int& curlen(); //recv length

private:
	std::shared_ptr<Packet> m_pkt;
	int m_nCurLen; //recv length

};


PHeader &PPacket::header()
{
	return m_pkt->header;
}
std::string &PPacket::body()
{
	return m_pkt->body;
}
std::string &PPacket::body(std::string& str)
{
	 m_pkt->body = str;
	 return m_pkt->body;
}
std::string &PPacket::data()
{
	return m_pkt->data;
}
PKT_STATUS &PPacket::status()
{
	return m_pkt->m_eStatus;
}
int &PPacket::curlen()
{
	return m_nCurLen;
}

#endif // !_SGS_PPACKET_H_

