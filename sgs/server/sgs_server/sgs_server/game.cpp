#include "game.h"
#include "player.h"
#include "app.h"
#include "ppacket.h"
#include "room.h"
#include "libgamelogic/sgslogic/sgsgamelogic.h"
#include "main.h"
#include "libs/json/json.h"
#include "jsonproto/jsonproto.h"

#include "libgamelogic/sgslogic/hero.h"

#define ROOM_ID_END 1000000
#define ROOM_ID_START 100000

Game::Game() : m_nStatus(0)
{
	m_mPlayers.clear();
	m_mRooms.clear();
}

Game::~Game()
{
}

int Game::StartUp()
{
	if (Listen() != 0)
	{
		return -1;
	}

	//add some need init
	Hero::GetALLhero();

	return -1;
}

int Game::ReqRegist(Player *player)
{
	int code = 0;

	Json::Value root;
	std::string err;

	if (!Game::ParseMsg(player,&root,err))
	{
		code = 0x01;
	}
	else
	{
		player->Set(root[SJPROTO[E_Player]]);

		//check account
		if (player->CheckAccount())
		{
			code = 0x02;
		}

		//check passwd
		if (player->CheckPasswd())
		{
			code |= 0x004;
		}
		if (0 == code)
		{
			if (1 != player->Regist())
			{
				code = 0x08; //
			}
		}
	}
	sgslog.info(FFL_s_d, "regist code:", code);

	root.clear();
	root["code"] = (code); //
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_REGIST_UC);
	player->Send(packet);

	/*proto::game::ReqRegist rgst;
	proto::game::ReqRegistUc rgstuc;
	if (!rgst.ParseFromString(player->m_iClient.m_iPacket.body))
	{
		code = 0x01;
	}
	else
	{
		player->Set(rgst.player());

		//check account
		if (player->CheckAccount())
		{
			code = 0x02;
		}

		//check passwd
		if (player->CheckPasswd())
		{
			code |= 0x004;
		}
		if (0 == code)
		{
			if (1 != player->Regist())
			{
				code = 0x08; //
			}
		}
	}
	sgslog.info(FFL_s_d,"regist code:",code);
	rgstuc.set_code(code); //
	std::shared_ptr<PPacket> packet(new PPacket());
	rgstuc.SerializeToString(&packet->body);
	packet->pack(PLAYER_REGIST_UC);

	player->Send(packet);*/

	return code;
}

int Game::ReqLogin(Player *player)
{
	int code = 0;
	Json::Value root;
	std::string err;

	if (!Game::ParseMsg(player,&root,err))
	{
		code = 0x01;
	}
	else
	{
		player->m_stAccount = root[SPlayer[EPlayer_account]].asString();
		player->m_stPasswd = root[SPlayer[EPlayer_passwd]].asString();

		//check account
		if (player->CheckAccount())
		{
			code = 0x02;
		}

		//check passwd
		if (player->CheckPasswd())
		{
			code |= 0x004;
		}
		if (0 == code)
		{
			if (1 != player->Login())
			{
				code = 0x08; //
			}
		}
	}
	sgslog.info(FFL_s_d, "login code:", code);
	root.clear();
	root["code"] = (code); //
	if (0 == code)
	{
		player->UpdateState(ST_PLAYER_ONLINE);
		player->Get(root[SJPROTO[E_Player]]);
	}
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_LOGIN_UC);
	player->Send(packet);

	return code;
}

int Game::ReqReady(Player *player)
{
	int code = 0;

	Json::Value root;
	std::string err;

	if (!Game::ParseMsg(player,&root,err))
	{
		code = 0x01;
	}
	else
	{
		if (root["ready"].asBool())
		{
			player->m_nGameStatus = ST_GM_PLAYER_READY;
			//player->m_pRoom->Ready(player);
		}
		else
		{
			player->m_nGameStatus = ST_GM_PLAYER_NONE;
		}
	}

	root.clear();
	root["code"] = (code); //
	if (0 == code)
	{
		player->Get(root[SJPROTO[E_Player]]);
	}
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_READY_BC);

	player->m_pRoom->Broadcast(packet);

	//to check start
	if (0 == code)
	{
		player->m_pRoom->CheckGameStart();
	}

	return code;
}

int Game::ReqUserQuit(Player *player)
{
	m_mPlayers.erase(player->m_iClient.m_nfd);
	//if (ST_PLAYER_OFFLINE != player->m_nStatus && player->m_nID >= 0)
	{
		player->UpdateState(ST_PLAYER_OFFLINE);
	}

	if(/*ST_GM_PLAYER_NONE != player->m_nGameStatus &&*/ NULL != player->m_pRoom)
	{
		//player->m_pRoom->QuitRoom(player);
		ReqQuitRoom(player);
	}

	delete player;
	return 0;
}

int Game::ReqUpdatePwd(Player *player)
{
	return 0;
}

int Game::ReqGetInfo(Player *player)
{
	return 0;
}

int Game::ReqGetFriends(Player *player)
{
	return 0;
}

int Game::ReqAddFriends(Player *player)
{
	return 0;
}

int Game::ReqDeleteFriends(Player *player)
{
	return 0;
}

int Game::ReqSelectGameMode(Player *player)
{
	return 0;
}

int Game::ReqGetGameMode(Player *player)
{
	return 0;
}

int Game::GetNewRoomID()
{
	srand((unsigned int)time(NULL));

	int id = (rand() % (ROOM_ID_END - ROOM_ID_START)) + ROOM_ID_START;

	while (m_mRooms.find(id) != m_mRooms.end())
	{
		id = ((id + 100) % (ROOM_ID_END - ROOM_ID_START)) + ROOM_ID_START;
	}

	return id;
}
int Game::ReqCreateRoom(Player *player)
{
	if (NULL == player)
	{
		return -1;
	}
	int code = 0;

	Json::Value root;
	std::string err;

	if (!Game::ParseMsg(player,&root,err))
	{
		code = 0x01;
	}
	else
	{
		GameLogic *plogic = new (std::nothrow) SGSGameLogic();
		if (NULL != plogic)
		{
			int roomid = GetNewRoomID();
			Room *room = new (std::nothrow) Room(plogic, roomid, (ERoomType)(root.get(SRoom[ERoom_type], ROOM_TYPE_2).asInt()),
												 root[SRoom[ERoom_name]].asString(), (EMatchSeatWay)(root.get(SRoom[ERoom_match_seat_way],MATCH_SEAT_ORDER).asInt()));
			if (NULL != room)
			{
				plogic->SetRoom(room);
				m_mRooms[roomid] = room;
				player->m_pRoom = room;
				room->m_pMaster = player;
				room->EnterRoom(player);

				root.clear();
				room->Get(root[SJPROTO[E_Room]]);
			}
			else
			{
				delete plogic; //new err
				code = 0x02;
			}
		}
		else
		{
			code = 0x04; //new err
		}
	}

	root["code"] = (code); //
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_CREATE_ROOM_UC);

	player->Send(packet);

	return code;
}
int Game::DeleteRoom(Room *room)
{
	return 0;
}

int Game::ReqMatchRoom(Player *player)
{
	return 0;
}

int Game::ReqEnterRoom(Player *player)
{
	if (NULL == player)
	{
		return -1;
	}
	int code = 0;

	std::map<int, Room *>::iterator room;
	Json::Value root;
	std::string err;

	if (!Game::ParseMsg(player,&root,err))
	{
		code = 0x01;
	}
	else
	{
		room = m_mRooms.find(root[SRoom[ERoom_room_id]].asInt());
		if (m_mRooms.end() != room)
		{
			if (0 != room->second->EnterRoom(player))
			{
				code = 0x02; //enter room failed
			}
		}
		else
		{
			code = 0x04; //not find the room
		}
	}

	root.clear();
	if (0 == code)
	{
		//player->Get(root[SJPROTO[E_Player]]);
		root[SJPROTO[E_Player]] = player->m_stAccount;
		room->second->Get(root[SJPROTO[E_Room]]);
	}

	root["code"] = (code);
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_ENTER_ROOM_BC);

	if (0 == code)
	{
		room->second->Broadcast(packet);
	}
	else
	{
		player->Send(packet);
	}

	return code;
}
int Game::ReqQuitRoom(Player *player)
{
	if (NULL == player)
	{
		return -1;
	}
	int code = 0;

	std::map<int, Room *>::iterator room;
	int quit_ret = 0;

	Json::Value root;
	std::string err;

//	if (!Game::ParseMsg(player,&root,err))
	{
//		code = 0x01;
	}
//	else
	{
		if(NULL != player->m_pRoom)
		{
			room = m_mRooms.find(player->m_pRoom->m_nRoomID);
			if (m_mRooms.end() != room)
			{
				if (-1 == (quit_ret = room->second->QuitRoom(player)))
				{
					code = 0x02; //enter room failed
				}
			}
			else
			{
				code = 0x04; //not find the room
			}
		}
	}

	root.clear();
	if (0 == code)
	{
		player->Get(root[SJPROTO[E_Player]]);
	}

	root["code"] = (code);
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_QUIT_ROOM_BC);

	if (0 == code)
	{
		player->Send(packet);
		room->second->Broadcast(packet);
		//all quit room ,delete room
		if (1 == quit_ret)
		{
			m_mRooms.erase(room);
			delete room->second;
		}
	}
	else
	{
		player->Send(packet);
	}

	return code;
}

int Game::ReqEnterRoomFast(Player *player)
{
	if (NULL == player)
	{
		return -1;
	}
	int code = 0;

	Room *room = NULL;

	Json::Value root;
	std::string err;

	if (!Game::ParseMsg(player,&root,err))
	{
		code = 0x01;
	}
	else
	{
		for (std::map<int, Room *>::iterator room_it = m_mRooms.begin(); room_it != m_mRooms.end(); ++room_it)
		{
			if (room_it->second->m_nPlayerCnt < room_it->second->m_nMaxPlayerCnt)
			{
				room = room_it->second;
				break;
			}
		}

		if (NULL != room)
		{
			if (0 != room->EnterRoom(player))
			{
				code = 0x02; //enter room failed
			}
		}
		else
		{
			code = 0x04; //not find the room
		}
	}
	root.clear();
	if (0 == code)
	{
		//player->Get(root[SJPROTO[E_Player]]);
		root[SJPROTO[E_Player]] = player->m_stAccount;
		room->Get(root[SJPROTO[E_Room]]);
	}

	root["code"] = (code);
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_ENTER_ROOM_BC);

	if (0 == code)
	{
		room->Broadcast(packet);
	}
	else
	{
		player->Send(packet);
	}

	return code;
}

int Game::ReqSearchRoom(Player *player)
{
	if (NULL == player)
	{
		return -1;
	}
	int code = 0;

	std::map<int, Room *>::iterator room;

	Json::Value root;
	std::string err;

	if (!Game::ParseMsg(player,&root,err))
	{
		code = 0x01;
	}
	else
	{
		room = m_mRooms.find(root[SRoom[ERoom_room_id]].asInt());
		if (m_mRooms.end() == room)
		{
			code = 0x02; //not find the room
		}
	}

	root.clear();
	if (0 == code)
	{
		room->second->Get(root[SJPROTO[E_Room]]);
	}

	root["code"] = (code);

	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_SEARCH_ROOM_UC);

	player->Send(packet);

	return code;
}

int Game::Broadcast(PPacket& pkt)
{
	for (std::map<int, Player *>::iterator player = m_mPlayers.begin(); player != m_mPlayers.end(); ++player)
	{
		player->second->Send(pkt);
	}
	return 0;
}

int Game::Unicast(Player *player, PPacket& pkt)
{
	player->Send(pkt);
	return 0;
}

const Player *Game::GetOLPlayer(int playerid)
{
	for (std::map<int, Player *>::iterator player = m_mPlayers.begin(); player != m_mPlayers.end(); ++player)
	{
		if (playerid == player->second->m_nID)
		{
			return player->second;
		}
	}

	return NULL;
}

int Game::Listen()
{
	sgslog.info(FFL_s_s_d, "Listening on:",
				g_app.m_iConf["app"]["host"].asString().c_str(),
				g_app.m_iConf["app"]["port"].asInt());

	struct sockaddr_in addr;

	m_nListenfd = socket(PF_INET, SOCK_STREAM, 0);
	if (m_nListenfd < 0)
	{
		sgslog.error(FFL_s, strerror(errno));
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(g_app.m_iConf["app"]["port"].asInt());
	addr.sin_addr.s_addr = inet_addr(g_app.m_iConf["app"]["host"].asString().c_str());
	if (addr.sin_addr.s_addr == INADDR_NONE)
	{
		sgslog.error(FFL_s, "Incorrect ip address!");
		close(m_nListenfd);
		m_nListenfd = -1;
		return -1;
	}

	int on = 1;
	if (setsockopt(m_nListenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		sgslog.error(FFL_s_s, "setsockopt failed:", strerror(errno));
		close(m_nListenfd);
		return -1;
	}

	if (bind(m_nListenfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		sgslog.error(FFL_s, "bind failed:", strerror(errno));
		close(m_nListenfd);
		return -1;
	}

	fcntl(m_nListenfd, F_SETFL, fcntl(m_nListenfd, F_GETFL, 0) | O_NONBLOCK);
	listen(m_nListenfd, 1000);

	m_iAccept.data = this;
	ev_io_init(&m_iAccept, Game::Accept_cb, m_nListenfd, EV_READ);
	ev_io_start(g_app.m_pLoop, &m_iAccept);
	sgslog.info(FFL_s, "listen ok");
	return 0;
}

void Game::Accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	if (EV_ERROR & revents)
	{
		sgslog.error(FFL_s, "got invalid event");
		return;
	}

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	int fd = accept(w->fd, (struct sockaddr *)&client_addr, &client_len);
	if (fd < 0)
	{
		sgslog.error(FFL_s_s, "accept error:", strerror(errno));
		return;
	}
	Game *game = (Game *)(w->data);

	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);

	Player *player = new (std::nothrow) Player(fd, inet_ntoa(client_addr.sin_addr));
	if (player)
	{
		player->m_iClient.Active();
		game->m_mPlayers[fd] = player;
	}
	else
	{
		close(fd);
	}
	return;
}

int Game::BeforeDo(Player *player)
{
	sgslog.info(FFLs);

	if (player->m_iClient.m_iPacket.check())
	{
		return 0;
	}
	//check state

	return -1;
}

int Game::Do(Player *player)
{
	int nRet = 0;

	if (player->m_iClient.m_iPacket.header().cmd > GAME_START && player->m_pRoom)
	{
		/*do game logic*/
		nRet = player->m_pRoom->Do(player);
	}
	else
	{
		/*do*/
		switch (player->m_iClient.m_iPacket.header().cmd)
		{
		case PLAYER_GET_FRIENDS:
			nRet = ReqGetFriends(player);
			break;
		case PLAYER_DELETE_FRIENDS:
			nRet = ReqDeleteFriends(player);
			break;
		case PLAYER_ADD_FRIENDS:
			nRet = ReqAddFriends(player);
			break;
		case PLAYER_UPDATE_PWD:
			nRet = ReqUpdatePwd(player);
			break;
		case PLAYER_MATCH_ROOM:
			nRet = ReqMatchRoom(player);
			break;
		case PLAYER_MATCH_ROOM_FAST:
			nRet = ReqEnterRoomFast(player);
			break;
		case PLAYER_ENTER_ROOM:
			nRet = ReqEnterRoom(player);
			break;
		case PLAYER_QUIT_ROOM:
			nRet = ReqQuitRoom(player);
			break;
		case PLAYER_SEARCH_ROOM:
			nRet = ReqSearchRoom(player);
			break;
		case PLAYER_READY:
			nRet = ReqReady(player);
			break;
		case PLAYER_SELECT_GAME_MODE:
			nRet = ReqSelectGameMode(player);
			break;
		case PLAYER_GET_GAME_MODE:
			nRet = ReqGetGameMode(player);
			break;
		case PLAYER_CREATE_ROOM:
			nRet = ReqCreateRoom(player);
			break;
		case PLAYER_REGIST:
			nRet = ReqRegist(player);
			break;
		case PLAYER_LOGIN:
			nRet = ReqLogin(player);
			break;
		case PLAYER_QUIT:
			nRet = ReqUserQuit(player);
			break;
		default:
			break;
		}
	}

	sgslog.info(FFL_s_d_d, "cmd:", player->m_iClient.m_iPacket.header().cmd, nRet);
	return nRet;
}

int Game::AfterDo(Player *player)
{
	sgslog.info(FFLs);

	player->m_iClient.m_iPacket.body().clear();
	player->m_iClient.m_iPacket.curlen() = 0;
	player->m_iClient.m_iPacket.status() = STAT_HEADER;

	return 0;
}

bool Game::ParseMsg(Player *player, void *msg, std::string &err)
{
	bool nRet = 0;
#if 1
	//json
	static Json::CharReaderBuilder m_jBuilder;
	static Json::CharReader *m_jReader = m_jBuilder.newCharReader();

	nRet = m_jReader->parse(player->m_iClient.m_iPacket.body().c_str(),
						  player->m_iClient.m_iPacket.body().c_str() + player->m_iClient.m_iPacket.body().length(), (Json::Value*)msg, &err);
#else
	//maybe protobuf

#endif

	return nRet;
}