#include <list>
#include <map>
#include <iostream>
#include <stdio.h>
#include <string>

#include "boost.asio.1.0.159/boost/asio.hpp"
#include "../Classes/libs/json/json.h"
#include "../Classes/libs/json/json-forwards.h"
#include "../ppacket.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "cocos2d.h"

#include "../jsonproto/jsonproto.h"

#include "sgsgameattr.h"
#include "player.h"
#include "room.h"
#include "proto.h"
#include "text.h"


extern std::list<std::shared_ptr<PPacket>> g_lstWrite;

extern Player u_player;
extern Room u_room;

extern CSGSTXT SGSTXT;
