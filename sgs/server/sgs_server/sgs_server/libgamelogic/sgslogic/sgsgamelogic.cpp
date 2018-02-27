#include "../../include.h"
#include "../../player.h"
#include "../../main.h"
#include "../../room.h"
#include "sgsgamelogic.h"
#include "sgsgameattr.h"
#include "sgscard.h"
#include "hero.h"
#include "../../libs/json/json.h"
#include "../../jsonproto/jsonproto.h"
#include "../../game.h"

extern const std::shared_ptr<Card> g_sgsCards[SGSCard::CARD_CNT];

SGSGameLogic::SGSGameLogic()
{
}
SGSGameLogic::~SGSGameLogic()
{
}

int SGSGameLogic::Do(Player *player)
{
    if (NULL != player)
    {
        switch (player->m_iClient.m_iPacket.header.cmd)
        {
        case GAME_OUT_CARD:
            break;
        case GAME_ABANDON_CARD:
            break;
        case GAME_USE_SKILL:
            break;
        case GAME_CANCEL_OUT_CARD:
            break;
        case GAME_OUT_CARD_END:
            break;
        case GAME_SELECT_CARD:
            break;
        default:
            break;
        }
    }
    return 0;
}
int SGSGameLogic::GameStart()
{
    int code = 0;
    Json::Value root;
    root.clear();

    InitCard();
    //先洗牌
    RandomCard();

    switch (m_pRoom->m_eType)
    {
    case ROOM_TYPE_2:
        Do2PStart(root);
        break;

    case ROOM_TYPE_6:
        Do6PStart(root);
        break;

    case ROOM_TYPE_8:
        break;
    default:
        break;
    }

    //广播结果

    root["code"] = (code); //

    PPacket *packet = (new PPacket());
    packet->body = root.toStyledString();
    packet->pack(GAME_START);

    m_pRoom->Broadcast(packet);

    return code;
}

void SGSGameLogic::RandomCard()
{
    srand((unsigned int)time(NULL));

    int nCardCnt = m_vCards.size();

    for (int i = nCardCnt - 1; i > 0; i--)
    {
        m_vCards[rand() % i].swap(m_vCards[i]);
    }

}

void SGSGameLogic::EnsureRoles()
{
}
void SGSGameLogic::Do2PStart(Json::Value &root)
{
    //
}

void SGSGameLogic::Do6PStart(Json::Value &root)
{
}

int SGSGameLogic::ReqOutCard(Player *player)
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
		root["card"].asInt();
	}

	root.clear();
	root["code"] = (code); //
	if(0 == code)
	{
		player->Get(root[SJPROTO[E_Player]]);
	}
	PPacket* packet = (new PPacket());
	packet->body = root.toStyledString();
	packet->pack(PLAYER_READY_BC);

	m_pRoom->Broadcast(packet);

	//to check start
	if(0 == code)
	{
		player->m_pRoom->CheckGameStart();
	}
	
	return code;
}
int SGSGameLogic::ReqAbandonCard(Player *player)
{
    return 0;
}
int SGSGameLogic::ReqUseSkill(Player *player)
{
    return 0;
}
int SGSGameLogic::ReqCancelOutCard(Player *player)
{
    return 0;
}
int SGSGameLogic::ReqSelectCard(Player *player)
{
    return 0;
}

void SGSGameLogic::Init()
{
}

void SGSGameLogic::InitCard()
{
    m_vCards.clear();
    for (int i = 0; i < SGSCard::CARD_CNT; ++i)
    {
        m_vCards.push_back(g_lstCards[i]);
    }
}

int SGSGameLogic::Enter(Player *player)
{
    int nRet = 0;
    std::shared_ptr<GameAttr> gm_attr = std::shared_ptr<GameAttr>(new (std::nothrow) SGSGameAttr());
    if (NULL != gm_attr && (size_t)m_pRoom->m_nMaxPlayerCnt > m_mPlayer.size())
    {
        int seat[8];
        memset(seat, 0x00, sizeof(seat));
        for (std::map<Player *, std::shared_ptr<GameAttr>>::iterator it = m_mPlayer.begin(); it != m_mPlayer.end(); ++it)
        {
            seat[it->second->m_nSeatId]++;
        }
        int i = 0;
        if (MATCH_SEAT_ORDER == m_pRoom->m_nMatchSeatWay)
        {
            for (; i < m_pRoom->m_nMaxPlayerCnt; ++i)
            {
                if (0 == seat[i])
                {
                    gm_attr->m_nSeatId = i;
                    break;
                }
            }
        }
        else
        {
            srand((unsigned int)time(NULL));

            int remain_seat = rand() % (m_pRoom->m_nMaxPlayerCnt - m_mPlayer.size());
            int cnt = 0;
            for (; i < m_pRoom->m_nMaxPlayerCnt; ++i)
            {
                if (0 == seat[i])
                {
                    if (cnt == remain_seat)
                    {
                        gm_attr->m_nSeatId = i;
                        break;
                    }
                    cnt++;
                }
            }
        }
        if (i >= m_pRoom->m_nMaxPlayerCnt)
        {
            nRet = -1;
        }
        else
        {
            m_mPlayer.insert(std::pair<Player *, std::shared_ptr<GameAttr>>(player, (gm_attr)));
        }
    }

    return nRet;
    //
}