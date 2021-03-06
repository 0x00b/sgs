#include "room.h"
#include "player.h"
#include "ppacket.h"
#include "app.h"
#include "game.h"

Room::Room(GameLogic* plogic, int roomid, ERoomType type, const std::string& name, EMatchSeatWay eway):
	m_pGmLgic(plogic),
	m_stName(name),
	m_eType(type),
	m_nRoomID(roomid),
	m_nMaxPlayerCnt(type),
	m_nPlayerCnt(0),
	m_nMatchSeatWay(eway),
	m_nStatus(ROOM_ST_NONE)
{
	m_lstPlayers.clear();
}


Room::~Room()
{
	delete m_pGmLgic;
}

int Room::EnterRoom(Player *player)
{
	if (NULL != player)
	{
		if (m_nPlayerCnt < m_nMaxPlayerCnt)
		{
			m_lstPlayers.push_back(player);
			m_pGmLgic->Enter(player);
			
			player->EnterRoom(this);

			m_nPlayerCnt++;

			return 0;
		}
		else
		{
			return 1;
		}
	}
	return -1;
}

int Room::QuitRoom(Player *player)
{
	if (NULL != player)
	{
		//if (ROOM_ST_READY >= m_nStatus)
		{
			m_lstPlayers.remove(player);
			m_nPlayerCnt--;
			player->QuitRoom();
			m_pGmLgic->Leave(player);

			if (0 >= m_nPlayerCnt)
			{
				//all player quit
				return 1;
			}
			else
			{
				if (player == m_pMaster) // mstart quit , need to select a new master
				{
					m_pMaster = m_lstPlayers.front(); //
				}
			}
			return 0;
		}
		//else
		{
		//	return 2;
		}
	}
	return -1;
}
/*
void Room::Get(proto::game::Room *proom)
{
	proom->set_name(m_stName);
	proom->set_type(m_eType);
	proom->set_room_id(m_nRoomID);
	proom->set_max_player_cnt(m_nMaxPlayerCnt);
	proom->set_player_cnt(m_nPlayerCnt);
	proom->set_match_seat_way(m_nMatchSeatWay);
	proom->set_status(m_nStatus);

	int index = 0;
	google::protobuf::RepeatedPtrField<proto::game::Player> *players =  proom->mutable_players();
	for (std::list<Player *>::iterator it = m_lstPlayers.begin(); it != m_lstPlayers.end(); ++it)
	{
		if (m_pMaster != *it)
		{
			proto::game::Player *player = players->Mutable(index++);
			(*it)->Get(player);
		}
	}

	proto::game::Player* master = proom->mutable_master();
	m_pMaster->Get(master);

}
void Room::Set(const proto::game::Room &proom)
{
	m_stName = proom.name();				//room's name
	m_eType = (ERoomType)proom.type();		//room type
	m_nMatchSeatWay = proom.match_seat_way();
}
*/

void Room::Get(Json::Value& proom)
{

	proom[SRoom[ERoom_name]] 			= (m_stName);
	proom[SRoom[ERoom_type]] 			= (m_eType);
	proom[SRoom[ERoom_room_id]] 		= (m_nRoomID);
	proom[SRoom[ERoom_max_player_cnt]] 	= (m_nMaxPlayerCnt);
	proom[SRoom[ERoom_player_cnt]] 		= (m_nPlayerCnt);
	proom[SRoom[ERoom_match_seat_way]] 	= (m_nMatchSeatWay);
	proom[SRoom[ERoom_status]] 			= (m_nStatus);

	int index = 0;
	for (std::list<Player *>::iterator it = m_lstPlayers.begin(); it != m_lstPlayers.end(); ++it)
	{
		//if (m_pMaster != *it)
		{
			(*it)->Get(proom[SJPROTO[E_Player]][index++]);
		}
	}


	//m_pMaster->Get(proom["master"]);
	proom["master"] = m_pMaster->m_stAccount;

}
void Room::Set(const Json::Value &proom)
{
	/*
	m_stName = proom.name();				//room's name
	m_eType = (ERoomType)proom.type();		//room type
	m_nMatchSeatWay = proom.match_seat_way();
	*/
}

int Room::Broadcast(PPacket& pkt)
{
	for (std::list<Player *>::iterator it = m_lstPlayers.begin(); it != m_lstPlayers.end(); ++it)
	{
		(*it)->Send(pkt);
	}
	return 0;
}

int Room::Unicast(Player * player, PPacket& pkt)
{
	player->Send(pkt);
	return 0;
}

int Room::Ready(Player * player)
{
	return 0;
}

int Room::Do(Player* player)
{
	if (NULL != m_pGmLgic)
	{
		return m_pGmLgic->Do(player);
	}
	return -1;
}

int Room::CheckGameStart()
{
	if(m_lstPlayers.size() == (size_t)m_nMaxPlayerCnt)
	{
		//chaek ready status
		int ready_cnt = 0;
		for (std::list<Player *>::iterator it = m_lstPlayers.begin(); it != m_lstPlayers.end(); ++it)
		{
			if(ST_GM_PLAYER_READY == (*it)->m_nGameStatus)
			{
				ready_cnt++;
			}
		}
		if (ready_cnt == m_nMaxPlayerCnt)
		{
			//start game
			m_nStatus = ROOM_ST_START;
			m_pGmLgic->GameStart();
		}
	}
	return 0;
}