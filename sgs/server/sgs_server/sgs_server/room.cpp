#include "room.h"
#include "player.h"
#include "ppacket.h"

Room::Room(GameLogic* plogic, int roomid, ERoomType type, const std::string& name):
	m_pGmLgic(plogic),
	m_stName(name),
	m_eType(type),
	m_nRoomID(roomid),
	m_nMaxPlayerCnt(type),
	m_nPlayerCnt(0),
	m_nMatchSeatWay(),
	m_nStatus(0)
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
	if(NULL != player)
	{
		m_pGmLgic->Leave(player);
		m_lstPlayers.remove(player);
		m_nPlayerCnt--;
		player->QuitRoom();
		return 0;
	}
	return -1;
}


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
		proto::game::Player* player =players->Mutable(index);
		(*it)->Get(player);
	}
}
void Room::Set(const proto::game::Room &proom)
{
	m_stName = proom.name();				//room's name
	m_eType = (ERoomType)proom.type();		//room type
}

int Room::Broadcast(PPacket* pkt)
{
	std::shared_ptr<PPacket> sptr(pkt);
	for (std::list<Player *>::iterator it = m_lstPlayers.begin(); it != m_lstPlayers.end(); ++it)
	{
		(*it)->Send(sptr);
	}
	return 0;
}

int Room::Unicast(Player * player, PPacket* pkt)
{
	std::shared_ptr<PPacket> sptr(pkt);
	player->Send(sptr);
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
			m_pGmLgic->GameStart();
		}
	}
	return 0;
}