#include "player.h"
#include "app.h"
#include "room.h"
#include "main.h"
#include "game.h"
#include "mysqlutil/mysqlutil.h"
#include "protoco/appproto.pb.h"

Player::Player(int fd, std::string stIP):m_iClient(this)
{
	m_iClient.m_nfd = fd;
	m_iClient.m_stIP = stIP;
}

int Player::ReqQuitRoom()
{
	return 0;
}

int Player::GetInfoByID()
{
	return 0;
}
/*
pkt must call pack func before call this function
*/
int Player::Send(PPacket & pkt)
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
	log.info(FFLs);

	if (m_iClient.m_iPacket.check())
	{
		return 0;
	}
	return -1;
}

int Player::Do()
{
	log.info(FFLs);
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
			nRet = ReqQuitRoom();
			break;
		case PLAYER_SEARCH_ROOM:
			nRet = g_app.m_pGame->ReqSearchRoom(this);
			break;
		case PLAYER_READY:
			nRet = m_pRoom->Ready(this);
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
			nRet = g_app.m_pGame->UserRegist(this);
			break;
		case PLAYER_LOGIN:
			nRet = g_app.m_pGame->UserLogin(this);
			break;
		case PLAYER_QUIT:
			nRet = g_app.m_pGame->UserQuit(this);
			break;
		default:
			break;
		}
	}

	return nRet;
}

int Player::AfterDo()
{
	log.info(FFLs);

	m_iClient.m_iPacket.body.clear();
	m_iClient.m_iPacket.m_nCurLen = 0;
	m_iClient.m_iPacket.m_eStatus = STAT_HEADER;

	return 0;
}


Player::~Player()
{
}

int Player::ReqRegist()
{
	return 0;
}

int Player::ReqLogin()
{
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
	std::string sql = "INSERT INTO `sgs_db`.`player` \
		(`account`, `passwd`, `sex`, `level`, `exp`, `status`, `regist_date`, `remark`) VALUES('";
	sql.append(m_stAccount).append("','").
		append(m_stPasswd).append("',");
	sql += m_chSex;
	sql.append(",");
	sql += m_sLevel;
	sql.append(",");
	sql += m_sExp;
	sql.append(",");
	sql += m_nStatus;
	sql.append(",'").
		append(m_stRegistDate).append("','").
		append(m_stRemark).append("');");

	res = MySqlUtil::MysqlQuery(sql.c_str());
	if (res)
	{
		mysql_free_result(res);
		return 0;
	}
	return -1;
}

int Player::Login()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string sql = "SELECT `player`.`idplayer`,\
		`player`.`passwd`,\
		`player`.`sex`,\
		`player`.`avatar`,\
		`player`.`level`,\
		`player`.`exp`,\
		`player`.`status`,\
		`player`.`regist_date`,\
		`player`.`remark`\
		FROM `sgs_db`.`player` WHERE 1=1 \
		";
	sql.append(" and `player`.`account` = '").append(m_stAccount + "';");

	res = MySqlUtil::MysqlQuery(sql.c_str());
	int nRet = 0;
	if (res)
	{
		std::string pwd("");
		int j = mysql_num_fields(res);
		while (row = mysql_fetch_row(res))
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
					pwd = row[i]; break;
				case 2:
					m_chSex = atoi(row[i]); break;
				case 3:
					m_stAvatar = row[i]; break;
				case 4:
					m_sLevel = atoi(row[i]); break;
				case 5:
					m_sExp = atoi(row[i]); break;
				case 6:
					m_nStatus = atoi(row[i]); break;
				case 7:
					m_stRegistDate = row[i]; break;
				case 8:
					m_stRemark = row[i]; break;
				default:
					break;
				}
			}
		}
		if (m_stPasswd != pwd)
		{
			nRet = -2;
		}
	}
	else
	{
		nRet = -1;
	}
	mysql_free_result(res);
	return nRet;
}

int Player::GetFriends(std::list<Player*>& list)
{
	return 0;
}

int Player::AddFriends()
{
	return 0;
}

int Player::DeleteFriends()
{
	return 0;
}
