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


PPacket::PPacket() :
	body(""), 
	data(""),
	m_eStatus(STAT_HEADER),
	m_nCurLen(0)
{
}


PPacket::~PPacket()
{
}

void PPacket::pack(unsigned int cmd, unsigned int uid, unsigned short svrid)
{
	header.cmd = cmd;
	header.uid = uid;
	header.svrid = svrid;
	header.len = body.length();
	data.clear();
	header.toNetStr(data);
	data.append(body);
}

void PPacket::pack(unsigned int cmd, std::string& body_ ,unsigned int uid, unsigned short svrid)
{
	header.cmd = cmd;
	header.uid = uid;
	header.svrid = svrid;
	header.len = body_.length();
	data.clear();
	header.toNetStr(data);
	data.append(body_);
}

int PPacket::save()
{
	header.cmd = ntohl(header.cmd);
	header.uid = ntohl(header.uid);
	header.len = ntohs(header.len);
	header.svrid = ntohs(header.svrid);
	return 0;
}

int PPacket::check()
{
	if ((size_t)header.len != body.length())
	{
		return -1;
	}
	return header.cmd;
}
