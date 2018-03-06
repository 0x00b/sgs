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
#include "../../app.h"


extern App g_app;

extern const std::shared_ptr<Card> g_sgsCards[SGSCard::CARD_CNT];

SHero::SHero(const std::shared_ptr<Hero> &hero) : m_bSelected(false),
                                                  m_pHero(hero)
{
}
SGSGameLogic::SGSGameLogic() : m_nSelected(0),
                               play_timer_stamp(15)
{
    play_timer.data = this;
    ev_timer_init(&play_timer, SGSGameLogic::play_timer_cb, play_timer_stamp, play_timer_stamp);
}
SGSGameLogic::~SGSGameLogic()
{
    ev_timer_stop(g_app.m_pLoop, &play_timer);
}

bool SGSGameLogic::HasSeat(int seatid)
{
    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator it = m_mPlayer.find(seatid);
    return ( it == m_mPlayer.end());
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
void SGSGameLogic::Reset()
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
        case GAME_DISCARD:
            code = ReqDiscard(player);
            break;
        case GAME_USE_SKILL:
            break;
        case GAME_CANCEL_OUT_CARD:
            break;
        case GAME_PLAY_CARD_END:
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

void SGSGameLogic::play_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
    SGSGameLogic *gl = (SGSGameLogic *)w->data;
    ev_timer_stop(g_app.m_pLoop, &gl->play_timer);

	int code = 0;
	Json::Value root;
    root.clear();
    int seatid = gl->m_pCurrPlayer->SeatID();

    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator it = gl->m_mPlayer.find(seatid);
    if (it != gl->m_mPlayer.end())
    {
        SGSGameAttr &ga = *it->second;
        for (int i = ga.m_pHero->blood; i < (int)ga.m_lstPlayerCards.size(); ++i)
        {
            root["cards"][i] = ga.m_lstPlayerCards.back()->card();
            ga.m_lstPlayerCards.pop_back();
        }
        root["code"] = (code); //
        PPacket packet;
        packet.body() = root.toStyledString();
        packet.pack(GAME_DISCARD_BC);

        gl->m_pRoom->Broadcast(packet);

        //下一个人出牌
        seatid = (seatid + 1) % gl->m_pRoom->m_eType;
        if (gl->m_mPlayer.find(seatid) != gl->m_mPlayer.end())
        {
            gl->m_pCurrPlayer = gl->m_mPlayer[seatid]->m_player;
            gl->PlayCardUC(gl->m_pCurrPlayer);
        }
        else
        {
            //有人退出啦
        }
    }
    else
    {
        code = 0x08;
    }

    return;
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

int SGSGameLogic::PlayCardUC(Player *player)
{
	Json::Value root;

    root["code"] = (0); //
    root["seatid"] = player->SeatID();
    PPacket packet;
    packet.body() = root.toStyledString();
    packet.pack(GAME_PLAY_CARD_BC);

    m_pRoom->Broadcast(packet);
    //开始出牌
    m_pCurrPlayer = player;
    ev_timer_again(g_app.m_pLoop, &play_timer);
    return 0;
}
int SGSGameLogic::ReqPlayCard(Player *player)
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
int SGSGameLogic::ReqDiscard(Player *player)
{
	int code = 0;
	Json::Value root;
	std::string err;

    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator it = m_mPlayer.find(player->SeatID());
    if (it != m_mPlayer.end())
    {
        if (!it->second->m_bSelectedHero)
        {
            if (!Game::ParseMsg(player, &root, err))
            {
                code = 0x01;
            }
            else
            {
                for (int i = 0; i < root["cards"].size(); ++i)
                {
                    //root["cards"][i] = ga.m_lstPlayerCards.back()->card();
                    //ga.m_lstPlayerCards.pop_back();
                }
            }
        }
    }
    else
    {
        code = 0x08;
    }
    root["code"] = (code); //
	PPacket packet;
	packet.body() = root.toStyledString(); 
	packet.pack(GAME_DISCARD_BC);

    m_pRoom->Broadcast(packet);
    return code;
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
    bool gm_start = false; //开始发牌

    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator sga = m_mPlayer.find(player->SeatID());
    if (sga != m_mPlayer.end())
    {
        if (!sga->second->m_bSelectedHero)
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
                        /*if ((*it)->m_bSelected)
                    {
                        code = 0x02; //已经被选择
                    }
                    else*/
                        {
                            //m_mPlayer[player]->m_vHeros.push_back(std::shared_ptr<Hero>(new Hero(*((*it)->m_pHero))));
                            sga->second->m_pHero = std::shared_ptr<Hero>(new Hero(*((*it)->m_pHero)));
                            sga->second->m_bSelectedHero = true;
                            (*it)->m_bSelected = true;
                            m_nSelected++;
                            if (m_nSelected == P2P_HERO_CNT)
                            {
                                //选择完英雄之后开始游戏
                                gm_start = true;
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
    }
    else
    {
        code = 0x08;
    }

    root.clear();
	root["code"] = (code); //
	if(0 == code)
	{
        root["seatid"] = player->SeatID();
        root["idhero"] = sga->second->m_pHero->idhero;
	}
	PPacket packet;
	packet.body() = root.toStyledString(); 
	packet.pack(GAME_SELECT_HERO_BC);

    m_pRoom->Broadcast(packet);
    //m_pRoom->Unicast(player, packet);

	if(0 == code && gm_start)
	{
        StartDeal();
	}

    return code;
}

int SGSGameLogic::StartDeal() //开始发牌
{
	Json::Value root;
    for (std::map<int, std::shared_ptr<SGSGameAttr>>::iterator it = m_mPlayer.begin(); it != m_mPlayer.end(); ++it)
    {
        SGSGameAttr &ga = *it->second;
        root.clear();
        root["code"] = (0); //
        root["seatid"] = ga.m_player->SeatID();
        for (int i = 0; i < ga.m_pHero->blood; ++i)
        {
            if(0 == m_vCards.size())
            {
                InitCard();
                RandomCard();
            }
            ga.m_lstPlayerCards.push_back(m_vCards.back());
            root["cards"][i] = ga.m_lstPlayerCards.back()->card();
            m_vCards.pop_back();
        }

        PPacket packet;
        packet.body() = root.toStyledString();
        packet.pack(GAME_DEAL_BC);

        m_pRoom->Unicast(ga.m_player, packet);
    }
    //开始出牌
    m_pCurrPlayer = m_mPlayer[0]->m_player;
    PlayCardUC(m_pCurrPlayer);

    return 0;
}

int SGSGameLogic::Deal(Player *player) //给player发牌
{
    return 0;
}

int SGSGameLogic::Enter(Player *player)
{
    int nRet = 0;
    std::shared_ptr<SGSGameAttr> gm_attr = std::shared_ptr<SGSGameAttr>(new (std::nothrow) SGSGameAttr());
    if (NULL != gm_attr && (size_t)m_pRoom->m_nMaxPlayerCnt > m_mPlayer.size())
    {
        int seat[8];
        memset(seat, 0x00, sizeof(seat));
        for (std::map<int, std::shared_ptr<SGSGameAttr>>::iterator it = m_mPlayer.begin(); it != m_mPlayer.end(); ++it)
        {
            //seat[it->second->m_nSeatId]++;
            if (-1 != it->first)
            {
                seat[it->first]++;
            }
        }
        int i = 0;
        if (MATCH_SEAT_ORDER == m_pRoom->m_nMatchSeatWay)
        {
            for (; i < m_pRoom->m_nMaxPlayerCnt; ++i)
            {
                if (0 == seat[i])
                {
                    player->m_nSeatId = i;
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
                        player->m_nSeatId = i;
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
            gm_attr->m_player = player;
            m_mPlayer.insert(std::pair<int, std::shared_ptr<SGSGameAttr>>(player->SeatID(), (gm_attr)));
        }
    }

    return nRet;
    //
}