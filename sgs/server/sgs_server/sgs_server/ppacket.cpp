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


PPacket::PPacket() :body(""), data("")
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

void PPacket::save(std::string str)
{
	body = str;
}

int PPacket::check()
{
	if ((size_t)header.len != body.length())
	{
		return -1;
	}
	return header.cmd;
}
