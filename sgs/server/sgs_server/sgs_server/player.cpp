#include "player.h"
#include "app.h"
#include "room.h"
#include "main.h"
#include "game.h"
#include "mysqlutil/mysqlutil.h"

Player::Player():m_iClient(this)
{
	Init();
	m_iClient.m_nfd = -1;
}

Player::Player(int fd, std::string stIP):m_iClient(this)
{
	Init();
	m_iClient.m_nfd = fd;
	m_iClient.m_stIP = stIP;
}


Player::~Player()
{
	if (m_nID >= 0)
	{
		UpdateState(ST_PLAYER_OFFLINE);
	}
}

void Player::Init()
{
	m_pRoom = NULL;						//entered room

	m_stAccount.clear();			//account
	m_stPasswd.clear();				//password
	m_stName.clear();				//player's name
	m_stAvatar.clear();				//head picture
	m_stRegistDate.clear();			//
	m_stRemark.clear();				//
										//ints
	m_nID = -1;
	m_nExp = 0;							//experience
								//
	m_sLevel = 0;						//level
								//
	m_chSex = 0;						//sex
	m_nStatus = ST_PLAYER_ONLINE;						//player's status
	m_nGameStatus = ST_GM_PLAYER_NONE;					//player's gaming status
}
void Player::Set(const proto::game::Player &player)
{
	m_stAccount = player.account();	
	m_stPasswd = player.passwd();
	m_stName = player.name();		
	m_stAvatar = player.avatar();		
	m_stRegistDate = player.registdate();	
	m_stRemark = player.remark();		
}
void Player::Get(proto::game::Player* player)
{
	player->set_id(m_nID);
	player->set_account(m_stAccount);	
	player->set_passwd(m_stPasswd);
	player->set_name(m_stName);		
	player->set_avatar(m_stAvatar);		
	player->set_registdate(m_stRegistDate);	
	player->set_remark(m_stRemark);		
	player->set_status(m_nStatus);		
	player->set_gamestatus(m_nGameStatus);	
	player->set_sex(m_chSex);	
	player->set_level(m_sLevel);	
	player->set_exp(m_nExp);	
	player->set_seatid(SeatID());
	
}

int Player::SeatID()
{
	if (NULL != m_pRoom)
	{
		return m_pRoom->m_pGmLgic->GetSeatID(this);
	}
	return -1;
}

std::string &Player::GetProtoMsg()
{
	return m_iClient.m_iPacket.body;
}

int Player::GetInfoByID()
{
	return 0;
}
/*
pkt must call pack func before call this function
*/
int Player::Send(std::shared_ptr<PPacket>& pkt)
{
	if (m_iClient.m_nfd > 0)
	{
		m_iClient.m_lstWrite.push_back(pkt);
		ev_io_start(g_app.m_pLoop, &m_iClient.m_ev_write);
		return 0;
	}

	return -1;
}


int Player::BeforeDo()
{
	sgslog.info(FFLs);

	if (m_iClient.m_iPacket.check())
	{
		return 0;
	}
	//check state

	return -1;
}

int Player::Do()
{
	int nRet = 0;
	if (m_iClient.m_iPacket.header.cmd > GAME_START && m_pRoom)
	{
		/*do game logic*/
		nRet = m_pRoom->Do(this);
	}
	else
	{
		/*do*/
		switch (m_iClient.m_iPacket.header.cmd)
		{
		case PLAYER_GET_FRIENDS:
			nRet = ReqGetFriends();
			break;
		case PLAYER_DELETE_FRIENDS:
			nRet = ReqDeleteFriends();
			break;
		case PLAYER_ADD_FRIENDS:
			nRet = ReqAddFriends();
			break;
		case PLAYER_UPDATE_PWD:
			nRet = ReqUpdatePwd();
			break;
		case PLAYER_MATCH_ROOM:
			nRet = g_app.m_pGame->ReqMatchRoom(this);
			break;
		case PLAYER_MATCH_ROOM_FAST:
			nRet = g_app.m_pGame->ReqEnterRoomFast(this);
			break;
		case PLAYER_ENTER_ROOM:
			nRet = g_app.m_pGame->ReqEnterRoom(this);
			break;
		case PLAYER_QUIT_ROOM:
			nRet = g_app.m_pGame->ReqQuitRoom(this);
			break;
		case PLAYER_SEARCH_ROOM:
			nRet = g_app.m_pGame->ReqSearchRoom(this);
			break;
		case PLAYER_READY:
			nRet = ReqReady();
			break;
		case PLAYER_SELECT_GAME_MODE:
			nRet = g_app.m_pGame->ReqSelectGameMode(this);
			break;
		case PLAYER_GET_GAME_MODE:
			nRet = g_app.m_pGame->ReqGetGameMode(this);
			break;
		case PLAYER_CREATE_ROOM:
			nRet = g_app.m_pGame->ReqCreateRoom(this);
			break;
		case PLAYER_REGIST:
			nRet = ReqRegist();
			break;
		case PLAYER_LOGIN:
			nRet = ReqLogin();
			break;
		case PLAYER_QUIT:
			nRet = g_app.m_pGame->UserQuit(this);
			break;
		default:
			break;
		}
	}
	sgslog.info(FFL_s_d_d, "cmd:", m_iClient.m_iPacket.header.cmd, nRet);
	return nRet;
}

int Player::AfterDo()
{
	sgslog.info(FFLs);

	m_iClient.m_iPacket.body.clear();
	m_iClient.m_iPacket.m_nCurLen = 0;
	m_iClient.m_iPacket.m_eStatus = STAT_HEADER;

	return 0;
}

int Player::CheckAccount()
{
	if (m_stAccount.length() < 3 || m_stAccount.length() > 15)
	{
		return 1;
	}
	// todo 

	return 0;
}
int Player::CheckPasswd()
{
	if (m_stPasswd.length() < 3 || m_stPasswd.length() > 15)
	{
		return 1;
	}
	// todo

	return 0;
}
int Player::ReqRegist()
{
	int code = 0;
	proto::game::ReqRegist rgst;
	proto::game::ReqRegistUc rgstuc;
	if (!rgst.ParseFromString(m_iClient.m_iPacket.body))
	{
		code = 0x01;
	}
	else
	{
		Set(rgst.player());

		//check account
		if (CheckAccount())
		{
			code = 0x02;
		}

		//check passwd
		if (CheckPasswd())
		{
			code |= 0x004;
		}
		if (0 == code)
		{
			if (1 != Regist())
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

	Send(packet);

	return code;
}

int Player::ReqLogin()
{
	int code = 0;
	proto::game::ReqLogin proto;
	proto::game::ReqLoginUc protouc;
	if (!proto.ParseFromString(m_iClient.m_iPacket.body))
	{
		code = 0x01;
	}
	else
	{
		m_stAccount = proto.account();
		m_stPasswd = proto.pwd();

		//check account
		if (CheckAccount())
		{
			code = 0x02;
		}

		//check passwd
		if (CheckPasswd())
		{
			code |= 0x004;
		}
		if (0 == code)
		{
			if (1 != Login())
			{
				code = 0x08; //
			}
		}
	}
	sgslog.info(FFL_s_d,"login code:",code);
	protouc.set_code(code); //
	if(0 == code)
	{
		UpdateState(ST_PLAYER_ONLINE);
		Get(protouc.mutable_player());
	}
	std::shared_ptr<PPacket> packet(new PPacket());
	protouc.SerializeToString(&packet->body);
	packet->pack(PLAYER_REGIST_UC);

	Send(packet);

	return 0;
}

int Player::ReqReady()
{
	int code = 0;
	proto::game::ReqReady proto;
	proto::game::ReqReadyBc protouc;
	if (!proto.ParseFromString(m_iClient.m_iPacket.body))
	{
		code = 0x01;
	}
	else
	{
		m_nGameStatus = ST_GM_PLAYER_READY;

		m_pRoom->Ready(this);
	}
	protouc.set_code(code); //
	if(0 == code)
	{
		Get(protouc.mutable_player());
	}
	PPacket* packet = (new PPacket());
	protouc.SerializeToString(&packet->body);
	packet->pack(PLAYER_READY_BC);

	m_pRoom->Broadcast(packet);

	//to check start

	if(0 == code)
	{
		m_pRoom->CheckGameStart();
	}
	return code;
}

int Player::QuitRoom()
{
	m_nGameStatus = ST_GM_PLAYER_NONE;
	m_pRoom = NULL;
	
	return 0;
}

int Player::EnterRoom(Room *room)
{
	m_pRoom = room;
	m_nGameStatus = ST_GM_PLAYER_NONE;

	return 0;
}

int Player::ReqUpdatePwd()
{
	return 0;
}

int Player::ReqGetInfo()
{
	return 0;
}

int Player::ReqGetFriends()
{
	return 0;
}

int Player::ReqAddFriends()
{
	return 0;
}

int Player::ReqDeleteFriends()
{
	return 0;
}

int Player::Regist()
{
	MYSQL_RES* res;
	//MYSQL_ROW row;
	std::string sql = "INSERT INTO `sgs_db`.`player`"
	"(`account`, `passwd`, `level`,`exp`, `status`,`regist_date`, `name`) VALUES('";
	sql.append(m_stAccount).append("',password('").
		append(m_stPasswd).append("'), 0, 0, 0, curdate(),'").append(m_stName+"');");

	sgslog.debug(FFL_s_s,"sql:",sql.c_str());

	if (MySqlUtil::MysqlQuery(res, sql.c_str()))
	{
		mysql_free_result(res);
		return 1;
	}
	return -1;
}

int Player::Login()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string sql = "SELECT `player`.`idplayer`,"
		"`player`.`sex`,"
		"`player`.`avatar`,"
		"`player`.`level`,"
		"`player`.`exp`,"
		"`player`.`status`,"
		"`player`.`regist_date`,"
		"`player`.`remark`"
		"`player`.`name`,"
		"FROM `sgs_db`.`player` WHERE 1=1 "
		;
	sql.append(" and `player`.`account` = '").append(m_stAccount + "' and `player`.`passwd`=password('" + m_stPasswd + "');");

	sgslog.debug(FFL_s_s,"sql:",sql.c_str());

	int nRet = 0;
	if ((nRet = MySqlUtil::MysqlQuery(res, sql.c_str())))
	{
		int j = mysql_num_fields(res);
		while ((row = mysql_fetch_row(res)))
		{
			for (int i = 0; i < j; i++)
			{
				if (row[i] == NULL)
				{
					continue;
				}
				switch (i)
				{
				case 0:
					m_nID = atoi(row[i]); break;
				case 1:
					m_chSex = atoi(row[i]); break;
				case 2:
					m_stAvatar = row[i]; break;
				case 3:
					m_sLevel = atoi(row[i]); break;
				case 4:
					m_nExp = atoi(row[i]); break;
				case 5:
					m_nStatus = atoi(row[i]); break;
				case 6:
					m_stRegistDate = row[i]; break;
				case 7:
					m_stRemark = row[i]; break;
				case 8:
					m_stName = row[i]; break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		nRet = -1;
	}
	mysql_free_result(res);
	return nRet;
}

int Player::GetFriends(std::list<std::shared_ptr<Player>>& list)
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string sql = "SELECT `player`.`idplayer`,"
		"player`.`sex`,"
		"player`.`avatar`,"
		"player`.`level`,"
		"player`.`status`,"
		"player`.`name`,"
		"FROM `sgs_db`.`player` WHERE "
		"player`.`idplayer` in(SELECT `friends`.`idfriend` FROM `friends` WHERE `friends`.`idplayer` = ";
	sql += m_nID;
	sql.append(");");
	
	sgslog.debug(FFL_s_s,"sql:",sql.c_str());

	int nRet = 0;
	if (MySqlUtil::MysqlQuery(res, sql.c_str()))
	{
		int j = mysql_num_fields(res);
		while ((row = mysql_fetch_row(res)))
		{
			Player* player = new Player();
			for (int i = 0; i < j; i++)
			{
				if (row[i] == NULL)
				{
					continue;
				}
				switch (i)
				{
				case 0:
					player->m_nID = atoi(row[i]); break;
				case 1:
				case 2:
					player->m_chSex = atoi(row[i]); break;
				case 3:
					player->m_stAvatar = row[i]; break;
				case 4:
					player->m_sLevel = atoi(row[i]); break;
				case 5:
					player->m_nStatus = atoi(row[i]); break;
				case 6:
					player->m_stName = row[i]; break;
				default:
					break;
				}
			}
			list.push_back(std::shared_ptr<Player>(player));
		}
		nRet = list.size();
	}
	else
	{
		nRet = -1;
	}
	mysql_free_result(res);

	return nRet;
}

int Player::AddFriends(int idfriend)
{
	MYSQL_RES* res;
	//MYSQL_ROW row;
	std::string sql = "INSERT INTO `sgs_db`.`friends` "
		"(`idplayer` , `idfriend` , `type` , `remark`) VALUES(";
	sql += m_nID;
	sql.append(",");
	sql += idfriend;
	sql.append(",0,'');");

	sgslog.debug(FFL_s_s,"sql:",sql.c_str());

	if (MySqlUtil::MysqlQuery(res, sql.c_str()))
	{
		mysql_free_result(res);
		return 1;
	}
	return -1;
}

int Player::DeleteFriends(int idfriend)
{
	MYSQL_RES* res;
	//MYSQL_ROW row;
	std::string sql = "DELETE FROM `sgs_db`.`friends` WHERE `friends`.`idplayer` = ";
	sql += m_nID;
	sql.append(" and `friends`.`idfriend` = ");
	sql += idfriend;
	sql.append("；");

	sgslog.debug(FFL_s_s,"sql:",sql.c_str());

	if (MySqlUtil::MysqlQuery(res, sql.c_str()))
	{
		mysql_free_result(res);
		return 1;
	}
	return 0;
}

int Player::UpdateState(EPlayerStatus status)
{
	MYSQL_RES *res;
	//MYSQL_ROW row;
	std::string sql = "UPDATE `sgs_db`.`player` SET `player`.`status`=";
	sql += status;
	sql.append("WHERE `player`.`idplayer`=");
	sql += m_nID;
	sql.append(";");

	sgslog.debug(FFL_s_s,"sql:",sql.c_str());

	if (MySqlUtil::MysqlQuery(res, sql.c_str()))
	{
		mysql_free_result(res);
		return 1;
	}
	return 0;
}