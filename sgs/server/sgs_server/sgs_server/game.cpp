#include "game.h"
#include "player.h"
#include "app.h"
#include "ppacket.h"
#include "room.h"
#include "libgamelogic/sgsgamelogic.h"
#include "protoco/appproto.pb.h"
#include "main.h"

#define ROOM_ID_END 1000000
#define ROOM_ID_START 100000

Game::Game() :m_nStatus(0)
{
	m_mPlayers.clear();
	m_mRooms.clear();
}


Game::~Game()
{
}

int Game::StartUp()
{
	if (Listen() == 0)
	{
		return 0;
	}
	return -1;
}

int Game::ReqRegist(Player* player)
{
	int code = 0;
	proto::game::ReqRegist rgst;
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
	/*if(0 == code)
	{
		Login();
		Get(rgstuc.mutable_player());
	}*/
	std::shared_ptr<PPacket> packet(new PPacket());
	rgstuc.SerializeToString(&packet->body);
	packet->pack(PLAYER_REGIST_UC);

	player->Send(packet);

	return code;
}

int Game::ReqLogin(Player* player)
{
	int code = 0;
	proto::game::ReqLogin proto;
	proto::game::ReqLoginUc protouc;
	if (!proto.ParseFromString(player->m_iClient.m_iPacket.body))
	{
		code = 0x01;
	}
	else
	{
		player->m_stAccount = proto.account();
		player->m_stPasswd = proto.pwd();

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
	sgslog.info(FFL_s_d,"login code:",code);
	protouc.set_code(code); //
	if(0 == code)
	{
		player->UpdateState(ST_PLAYER_ONLINE);
		player->Get(protouc.mutable_player());
	}
	std::shared_ptr<PPacket> packet(new PPacket());
	protouc.SerializeToString(&packet->body);
	packet->pack(PLAYER_REGIST_UC);

	player->Send(packet);

	return 0;
}

int Game::ReqReady(Player* player)
{
	int code = 0;
	proto::game::ReqReady proto;
	proto::game::ReqReadyBc protouc;
	if (!proto.ParseFromString(player->m_iClient.m_iPacket.body))
	{
		code = 0x01;
	}
	else
	{
		player->m_nGameStatus = ST_GM_PLAYER_READY;

		player->m_pRoom->Ready(player);
	}
	protouc.set_code(code); //
	if(0 == code)
	{
		player->Get(protouc.mutable_player());
	}
	PPacket* packet = (new PPacket());
	protouc.SerializeToString(&packet->body);
	packet->pack(PLAYER_READY_BC);

	player->m_pRoom->Broadcast(packet);

	//to check start
	if(0 == code)
	{
		player->m_pRoom->CheckGameStart();
	}
	return code;
}

int Game::ReqUserQuit(Player * player)
{
	m_mPlayers.erase(player->m_iClient.m_nfd);
	if (ST_PLAYER_OFFLINE != player->m_nStatus)
	{
		player->UpdateState(ST_PLAYER_OFFLINE);
	}
	delete player;
	return 0;
}


int Game::ReqUpdatePwd(Player* player)
{
	return 0;
}

int Game::ReqGetInfo(Player* player)
{
	return 0;
}

int Game::ReqGetFriends(Player* player)
{
	return 0;
}

int Game::ReqAddFriends(Player* player)
{
	return 0;
}

int Game::ReqDeleteFriends(Player* player)
{
	return 0;
}



int Game::ReqSelectGameMode(Player * player)
{
	return 0;
}

int Game::ReqGetGameMode(Player * player)
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
int Game::ReqCreateRoom(Player * player)
{
	if(NULL == player)
	{
		return -1;
	}
	int code = 0;
	proto::game::ReqCreateRoom crproto;
	proto::game::ReqCreateRoomUc crprotouc;

	if(!crproto.ParseFromString(player->GetProtoMsg()))
	{
		code = 0x01;
	}
	else
	{
		GameLogic *plogic = new (std::nothrow) SGSGame();
		if (NULL != plogic)
		{
			int roomid = GetNewRoomID();
			Room *room = new (std::nothrow) Room(plogic,roomid, (ERoomType)crproto.room().type(),crproto.room().name());
			if (NULL != room)
			{
				plogic->Init(room);
				m_mRooms[roomid] = room;
				player->m_pRoom = room;
				room->m_pMaster = player;
				room->EnterRoom(player);

				proto::game::Room* proom = crprotouc.mutable_room();
				room->Get(proom);

			}
			else
			{
				delete plogic;//new err
				code = 0x02;
			}
		}
		else
		{
			code = 0x04;//new err
		}
	}

	crprotouc.set_code(code);
	std::shared_ptr<PPacket> packet(new PPacket());
	crprotouc.SerializeToString(&packet->body);
	packet->pack(PLAYER_CREATE_ROOM_UC);

	player->Send(packet);

	return code;
}
int Game::DeleteRoom(Room *room)
{
	return 0;
}

int Game::ReqMatchRoom(Player * player)
{
	return 0;
}

int Game::ReqEnterRoom(Player * player)
{
	if(NULL == player)
	{
		return -1;
	}
	int code = 0;
	proto::game::ReqEnterRoom erproto;
	proto::game::ReqEnterRoomBc erprotobc;
	std::map<int, Room*>::iterator room ;

	if(!erproto.ParseFromString(player->GetProtoMsg()))
	{
		code = 0x01;
	}
	else
	{
		room = m_mRooms.find(erproto.roomid());
		if(m_mRooms.end() != room)
		{
			if(0 != room->second->EnterRoom(player))
			{
				code = 0x02;//enter room failed
			}
		}
		else
		{
			code = 0x04;//not find the room
		}
	}

	if(0 == code)
	{
		proto::game::Player* pplayer = erprotobc.mutable_player();
		proto::game::Room* proom = erprotobc.mutable_room();
		player->Get(pplayer);
		room->second->Get(proom);
	}

	erprotobc.set_code(code);
	PPacket* packet = new PPacket();
	erprotobc.SerializeToString(&packet->body);
	packet->pack(PLAYER_ENTER_ROOM_BC);

	if(0 == code)
	{
		room->second->Broadcast(packet);
	}
	else
	{
		std::shared_ptr<PPacket> sppacket(packet);
		player->Send(sppacket);
	}

	return code;
}
int Game::ReqQuitRoom(Player * player)
{
	if(NULL == player)
	{
		return -1;
	}
	int code = 0;
	proto::game::ReqQuitRoom qrproto;
	proto::game::ReqQuitRoomBc qrprotobc;

	std::map<int, Room*>::iterator room ;
	int quit_ret = 0;
	
	if(!qrproto.ParseFromString(player->GetProtoMsg()))
	{
		code = 0x01;
	}
	else
	{
		room = m_mRooms.find(qrproto.roomid());
		if(m_mRooms.end() != room)
		{
			if(0 != (quit_ret = room->second->QuitRoom(player)))
			{
				code = 0x02;//enter room failed
			}
		}
		else
		{
			code = 0x04;//not find the room
		}
	}

	if(0 == code)
	{
		proto::game::Player* pplayer = qrprotobc.mutable_player();
		player->Get(pplayer);
	}

	qrprotobc.set_code(code);
	PPacket* packet = new PPacket();
	qrprotobc.SerializeToString(&packet->body);
	packet->pack(PLAYER_QUIT_ROOM_BC);

	if(0 == code)
	{
		room->second->Broadcast(packet);
		//all quit room ,delete room 
		if(1 == quit_ret)
		{
			m_mRooms.erase(room);
			delete room->second;
		}
	}
	else
	{
		std::shared_ptr<PPacket> sppacket(packet);
		player->Send(sppacket);
	}

	return code;
}

int Game::ReqEnterRoomFast(Player * player)
{
	if(NULL == player)
	{
		return -1;
	}
	int code = 0;
	proto::game::ReqEnterRoomFast erf_proto;
	proto::game::ReqEnterRoomBc erf_protobc;
	Room* room = NULL;

	if(!erf_proto.ParseFromString(player->GetProtoMsg()))
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
				code = 0x02;//enter room failed
			}
		}
		else
		{
			code = 0x04;//not find the room
		}
	}

	if(0 == code)
	{
		proto::game::Player* pplayer = erf_protobc.mutable_player();
		proto::game::Room* proom = erf_protobc.mutable_room();
		player->Get(pplayer);
		room->Get(proom);
	}

	erf_protobc.set_code(code);
	PPacket* packet = new PPacket();
	erf_protobc.SerializeToString(&packet->body);
	packet->pack(PLAYER_ENTER_ROOM_BC);

	if(0 == code)
	{
		room->Broadcast(packet);
	}
	else
	{
		std::shared_ptr<PPacket> sppacket(packet);
		player->Send(sppacket);
	}

	return code;
}

int Game::ReqSearchRoom(Player * player)
{
	if(NULL == player)
	{
		return -1;
	}
	int code = 0;
	proto::game::ReqSearchRoom rsr_proto;
	proto::game::ReqSearchRoomUc rsr_protouc;
	std::map<int, Room*>::iterator room ;

	if(!rsr_proto.ParseFromString(player->GetProtoMsg()))
	{
		code = 0x01;
	}
	else
	{
		room = m_mRooms.find(rsr_proto.roomid());
		if(m_mRooms.end() == room)
		{
			code = 0x02;//not find the room
		}
	}

	if(0 == code)
	{
		proto::game::Room* proom = rsr_protouc.mutable_room();
		room->second->Get(proom);
	}

	rsr_protouc.set_code(code);

	std::shared_ptr<PPacket> packet(new PPacket());
	rsr_protouc.SerializeToString(&packet->body);
	packet->pack(PLAYER_SEARCH_ROOM_UC);

	player->Send(packet);

	return code;
}

int Game::Broadcast(PPacket* pkt)
{
	std::shared_ptr<PPacket> sptr(pkt);
	for (std::map<int, Player *>::iterator player = m_mPlayers.begin(); player != m_mPlayers.end(); ++player)
	{
		player->second->Send(sptr);
	}
	return 0;
}

int Game::Unicast(Player * player, PPacket* pkt)
{
	std::shared_ptr<PPacket> sptr(pkt);
	player->Send(sptr);
	return 0;
}

const Player * Game::GetOLPlayer(int playerid)
{
	for (std::map<int, Player*>::iterator player = m_mPlayers.begin(); player != m_mPlayers.end(); ++player)
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
	sgslog.info(FFL_s_s_d,"Listening on:",
		g_app.m_iConf["app"]["host"].asString().c_str(),
		g_app.m_iConf["app"]["port"].asInt());

	struct sockaddr_in addr;

	m_nListenfd = socket(PF_INET, SOCK_STREAM, 0);
	if (m_nListenfd < 0) {
		sgslog.error(FFL_s, strerror(errno));
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(g_app.m_iConf["app"]["port"].asInt());
	addr.sin_addr.s_addr = inet_addr(g_app.m_iConf["app"]["host"].asString().c_str());
	if (addr.sin_addr.s_addr == INADDR_NONE) {
		sgslog.error(FFL_s,"Incorrect ip address!");
		close(m_nListenfd);
		m_nListenfd = -1;
		return -1;
	}

	int on = 1;
	if (setsockopt(m_nListenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
		sgslog.error(FFL_s_s,"setsockopt failed:", strerror(errno));
		close(m_nListenfd);
		return -1;
	}

	if (bind(m_nListenfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		sgslog.error(FFL_s,"bind failed:", strerror(errno));
		close(m_nListenfd);
		return -1;
	}

	fcntl(m_nListenfd, F_SETFL, fcntl(m_nListenfd, F_GETFL, 0) | O_NONBLOCK);
	listen(m_nListenfd, 1000);

	m_iAccept.data = this;
	ev_io_init(&m_iAccept, Game::Accept_cb, m_nListenfd, EV_READ);
	ev_io_start(g_app.m_pLoop, &m_iAccept);
	sgslog.info(FFL_s,"listen ok");
	return 0;
}

void Game::Accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	if (EV_ERROR & revents) {
		sgslog.error(FFL_s, "got invalid event");
		return;
	}

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	int fd = accept(w->fd, (struct sockaddr *) &client_addr, &client_len);
	if (fd < 0) {
		sgslog.error(FFL_s_s, "accept error:", strerror(errno));
		return;
	}
	Game *game = (Game*)(w->data);

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
