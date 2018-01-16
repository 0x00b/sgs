#include "player.h"
#include "app.h"
#include "room.h"
#include "main.h"
#include "game.h"
#include "mysqlutil/mysqlutil.h"

Player::Player(int fd, std::string stIP):m_iClient(this)
{
	m_iClient.m_nfd = fd;
	m_iClient.m_stIP = stIP;
}


Player::~Player()
{
}

int Player::GetFriends()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	res = MySqlUtil::MysqlQuery("select * from user where `user`.usr_delete != 1 or ISNULL( `user`.usr_delete )");
	if (res)
	{
		int j = mysql_num_fields(res);
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < j; i++)
			{
				if (row[i] == NULL)
				{
					continue;
				}/*
				switch (i)
				{
				case 0:
					usr->id = atoi(row[i]); break;
				case 1:
					strcpy_s(usr->account, row[i]); break;
				case 2:
					strcpy_s(usr->name, row[i]); break;
				case 3:
					strcpy_s(usr->pwd, row[i]); break;
				case 4:
					strcpy_s(usr->ip, row[i]); break;
				case 5:
					usr->port = atoi(row[i]); break;
				case 6:
					usr->online = atoi(row[i]); break;
				case 7:break;
				default:
					break;
				}*/
			}
		}
	}
	mysql_free_result(res);
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

int Player::QuitRoom()
{
	return 0;
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
			nRet = GetFriends();
			break;
		case PLAYER_DELETE_FRIENDS:
			nRet = DeleteFriends();
			break;
		case PLAYER_ADD_FRIENDS:
			nRet = AddFriends();
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
			nRet = QuitRoom();
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
