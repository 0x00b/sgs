#include "ppacket.h"


std::string& PHeader::toNetStr(std::string& str)
{
	struct PHeader phd;
	str.clear();
	phd.cmd = htonl(cmd);
	phd.uid = htonl(uid);
	phd.len = htons(len);
	phd.svrid = htons(svrid);
	str.append((const char*)&phd, sizeof(struct PHeader));

	return str;
}


Packet::Packet() :
	body(""), 
	data(""),
	m_eStatus(STAT_HEADER)
{
}


Packet::~Packet()
{
}

void PPacket::pack(unsigned int cmd, unsigned int uid, unsigned short svrid)
{
	m_pkt->header.cmd = cmd;
	m_pkt->header.uid = uid;
	m_pkt->header.svrid = svrid;
	m_pkt->header.len = m_pkt->body.length();
	m_pkt->data.clear();
	m_pkt->header.toNetStr(m_pkt->data);
	m_pkt->data.append(m_pkt->body);
}

void PPacket::pack(unsigned int cmd, std::string& body_ ,unsigned int uid, unsigned short svrid)
{
	m_pkt->header.cmd = cmd;
	m_pkt->header.uid = uid;
	m_pkt->header.svrid = svrid;
	m_pkt->header.len = body_.length();
	m_pkt->data.clear();
	m_pkt->header.toNetStr(m_pkt->data);
	m_pkt->data.append(body_);
}

int PPacket::save()
{
	m_pkt->header.cmd = ntohl(m_pkt->header.cmd);
	m_pkt->header.uid = ntohl(m_pkt->header.uid);
	m_pkt->header.len = ntohs(m_pkt->header.len);
	m_pkt->header.svrid = ntohs(m_pkt->header.svrid);
	return 0;
}

int PPacket::check()
{
	if ((size_t)m_pkt->header.len != m_pkt->body.length())
	{
		return -1;
	}
	return m_pkt->header.cmd;
}


PPacket::PPacket():
	m_pkt(new Packet()),
	m_nCurLen(0)
{
}

PPacket::PPacket(std::shared_ptr<Packet>& pkt):
	m_pkt(pkt),
	m_nCurLen(0)
{
}

PPacket::PPacket(const PPacket& pkt):
	m_pkt(pkt.m_pkt),
	m_nCurLen(0)
{
}
