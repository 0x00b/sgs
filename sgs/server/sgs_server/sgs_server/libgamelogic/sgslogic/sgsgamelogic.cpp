#include "../../include.h"
#include "../../player.h"
#include "../../main.h"
#include "../../room.h"
#include "sgsgamelogic.h"
#include "sgsgameattr.h"
#include "sgscard.h"
#include "../../libs/json/json.h"
#include "../../jsonproto/jsonproto.h"
#include "../../game.h"

extern const std::shared_ptr<Card> g_sgsCards[SGSCard::CARD_CNT];

SHero::SHero(const std::shared_ptr<Hero> &hero) : m_bSelected(false),
                                                  m_pHero(hero)
{
}
SGSGameLogic::SGSGameLogic() : m_nSelected(0),
                               m_nCurrPlayerID(0)
{
}
SGSGameLogic::~SGSGameLogic()
{
}

int SGSGameLogic::Do(Player *player)
{
    int code = 0;
    if (NULL != player)
    {
        switch (player->m_iClient.m_iPacket.header().cmd)
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
        case GAME_SELECT_HERO:
            code = ReqSelectHero(player);
            break;
        default:
            break;
        }
    }
    return code;
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
        code = Do2PStart(root);
        break;

    case ROOM_TYPE_6:
        code = Do6PStart(root);
        break;

    case ROOM_TYPE_8:
        break;
    default:
        break;
    }

    //广播结果
    if(0 == code)
    {
        m_pRoom->m_nStatus = ST_GM_START;
    }

    root["code"] = (code); //

	PPacket packet;
	packet.body() = root.toStyledString();
    packet.pack(GAME_START);

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
int SGSGameLogic::Do2PStart(Json::Value &root)
{
    int i = 0;
    m_vSelcectHero.clear();
    for (std::vector<std::shared_ptr<Hero>>::iterator it = Hero::g_Heros.begin();i < P2P_CAN_SELECT_HERO_CNT && it != Hero::g_Heros.end() ;++i,++it)
    {
        m_vSelcectHero.push_back(std::shared_ptr<SHero>(new SHero(*it)));
        (*it)->Get(root["hero"][i]);
    }
    return 0;
}

int SGSGameLogic::Do6PStart(Json::Value &root)
{
    return 0;
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
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(PLAYER_READY_BC);

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

int SGSGameLogic::ReqSelectHero(Player *player)
{
	int code = 0;
	
	Json::Value root;
	std::string err;
    if (m_nCurrPlayerID == player->m_nID)
    {
        if (!Game::ParseMsg(player, &root, err))
        {
            code = 0x01;
        }
        else
        {
            int idhero = root.get("idhero", 0).asInt();
            for (std::vector<std::shared_ptr<SHero>>::iterator it = m_vSelcectHero.begin(); it != m_vSelcectHero.end(); ++it)
            {
                if (idhero == (*it)->m_pHero->idhero)
                {
                    if ((*it)->m_bSelected)
                    {
                        code = 0x02; //已经被选择
                    }
                    else
                    {
                        m_mPlayer[player]->m_vHeros.push_back(std::shared_ptr<Hero>(new Hero(*((*it)->m_pHero))));
                        (*it)->m_bSelected = true;
                        m_nSelected++;
                        if (m_nSelected == P2P_HERO_CNT)
                        {
                            
                        }
                    }
                    break;
                }
            }
        }
    }
    else
    {
        code = 0x04;
    }

    root.clear();
	root["code"] = (code); //
	if(0 == code)
	{
		//player->Get(root[SJPROTO[E_Player]]);
	}
	PPacket packet;
	packet.body() = root.toStyledString(); 
	packet.pack(GAME_SELECT_HERO_BC);

	m_pRoom->Broadcast(packet);
	
	return code;
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
    std::shared_ptr<SGSGameAttr> gm_attr = std::shared_ptr<SGSGameAttr>(new (std::nothrow) SGSGameAttr());
    if (NULL != gm_attr && (size_t)m_pRoom->m_nMaxPlayerCnt > m_mPlayer.size())
    {
        int seat[8];
        memset(seat, 0x00, sizeof(seat));
        for (std::map<Player *, std::shared_ptr<SGSGameAttr>>::iterator it = m_mPlayer.begin(); it != m_mPlayer.end(); ++it)
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
            m_mPlayer.insert(std::pair<Player *, std::shared_ptr<SGSGameAttr>>(player, (gm_attr)));
        }
    }

    return nRet;
    //
}