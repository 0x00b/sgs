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
                               m_nStatus(PLAYER_NONE),
                               play_timer_stamp(3),
                               discard_timer_stamp(10)
{
    play_timer.data = this;
    ev_timer_init(&play_timer, SGSGameLogic::play_timer_cb, play_timer_stamp, play_timer_stamp);

    discard_timer.data = this;
    ev_timer_init(&discard_timer, SGSGameLogic::discard_timer_cb, discard_timer_stamp, discard_timer_stamp);
}
SGSGameLogic::~SGSGameLogic()
{
    ev_timer_stop(g_app.m_pLoop, &play_timer);
    ev_timer_stop(g_app.m_pLoop, &discard_timer);
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
        if (g_lstCards[i]->func() != SGSCard::CARD_SHA 
        && g_lstCards[i]->func() != SGSCard::CARD_SHAN 
        && g_lstCards[i]->func() != SGSCard::CARD_TAO)
        {
            continue;
        }
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
            code = ReqPlayCard(player);
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
void SGSGameLogic::discard_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
    SGSGameLogic *gl = (SGSGameLogic *)w->data;
    ev_timer_stop(g_app.m_pLoop, &gl->discard_timer);

	int code = 0;
	Json::Value root;
    root.clear();
    int seatid = gl->m_nCurrPlayerSeat;

    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator it = gl->m_mPlayer.find(seatid);
    if (it != gl->m_mPlayer.end())
    {
        SGSGameAttr &ga = *it->second;
        int cnt = (int)ga.m_lstPlayerCards.size() - ga.m_pHero->blood;
        for (int i = 0 ; i < cnt; ++i)
        {
            root["cards"][i] = ga.m_lstPlayerCards.back()->card();
            ga.m_lstPlayerCards.pop_back();
        }
        root["code"] = (code); //
        root["seatid"] = (ga.m_player->SeatID()); //
        root["card_cnt"] = ga.m_lstPlayerCards.size();
        PPacket packet;
        packet.body() = root.toStyledString();
        packet.pack(GAME_DISCARD_BC);

        gl->m_pRoom->Broadcast(packet);

        //下一个人出牌
        gl->PlayCardUC((seatid + 1) % gl->m_pRoom->m_nMaxPlayerCnt);
    }
    else
    {
        code = 0x08;
    }

    return;
}

void SGSGameLogic::play_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
    SGSGameLogic *gl = (SGSGameLogic *)w->data;
    ev_timer_stop(g_app.m_pLoop, &gl->play_timer);

	Json::Value root;
    root.clear();
    int seatid = gl->m_nCurrPlayerSeat;

    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator it = gl->m_mPlayer.find(seatid);
    if (it != gl->m_mPlayer.end())
    {
        gl->DisCardUC(it->second->m_player);
    }
    else
    {
        
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

int SGSGameLogic::PlayCardUC(int seat)
{
	Json::Value root;
    int code  = 0;
    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator tsga = m_mPlayer.find(seat);
    if (tsga == m_mPlayer.end())
    {
        code = 0x01;
        //有人退出啦
    }
    else
    {
        Deal(*tsga->second, root, 2);
    }
    m_nStatus = PLAYER_PLAY_CARD;
    m_nCurrPlayerSeat = m_nCurrOutSeat = seat;

    root["code"] = code; //
    root["seatid"] = seat;
    PPacket packet;
    packet.body() = root.toStyledString();
    packet.pack(GAME_PLAY_CARD_BC);

    m_pRoom->Broadcast(packet);
    //开始出牌
    ev_timer_again(g_app.m_pLoop, &play_timer);
    return code;
}

int SGSGameLogic::DisCardUC(Player *player)
{
	Json::Value root;
    int code = 0;
    int seat = player->SeatID();

    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator sga = m_mPlayer.find(seat);
    if (sga != m_mPlayer.end())
    {
        if (sga->second->m_pHero->blood < (int)sga->second->m_lstPlayerCards.size() )
        {
            //弃牌
            m_nStatus = PLAYER_DISCARD;
            sga->second->m_nDiscardCnt = sga->second->m_lstPlayerCards.size() - sga->second->m_pHero->blood;
            root["discard_cnt"] = sga->second->m_nDiscardCnt;
        }
        else
        {
            //到下一个人出牌
            PlayCardUC((seat + 1) % m_pRoom->m_nMaxPlayerCnt);
            return 0x02;
        }
    }
    else
    {
        code = 0x01;
    }

    root["code"] = code; //
    root["seatid"] = seat;
    PPacket packet;
    packet.body() = root.toStyledString();
    packet.pack(GAME_DISCARD_UC);

    m_pRoom->Unicast(player, packet);
    //开始出牌
    ev_timer_again(g_app.m_pLoop, &discard_timer);

    return 0;
}

int SGSGameLogic::CanPlayCard(Player *player, int card)
{
    return 1;
}
int SGSGameLogic::ReqPlayCard(Player *player)
{
	int code = 0;
	
	Json::Value root;
	Json::Value result;
	std::string err;
    int card = 0;
    bool find = false;
    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator sga = m_mPlayer.end();
    std::list<std::shared_ptr<SGSCard>>::iterator it;
    int seat = player->SeatID();
    if (PLAYER_PLAY_CARD == m_nStatus)
    {
        if (!Game::ParseMsg(player, &root, err))
        {
            code = 0x01;
        }
        else
        {
            if (seat == m_nCurrPlayerSeat)
            {
                card = root["card"].asInt();
                sga = m_mPlayer.find(seat);
                if (sga != m_mPlayer.end())
                {
                    std::list<std::shared_ptr<SGSCard>> &lstcard = sga->second->m_lstPlayerCards;
                    for (it = lstcard.begin(); it != lstcard.end(); ++it)
                    {
                        if ((*it)->card() == card)
                        {
                            find = true;
                            break;
                        }
                    }
                }
                else
                {
                    code = 0x04;
                }
                if (!find)
                {
                    code = 0x08;
                }
            }
            else
            {
                code = 0x10;
            }
        }
    }
    else
    {
        code = 0x11;
    }

    if (0 == code && find)
    {
        if (CanPlayCard(player, card))//能出这张牌
        {
            ev_timer_stop(g_app.m_pLoop, &play_timer);
            sga->second->m_lstPlayerCards.erase(it);
        }
    }
	result["code"] = code; //
	result["card"] = card; //
	result["seatid"] = seat; //
    if(sga != m_mPlayer.end())
    {
        result["card_cnt"] = sga->second->m_lstPlayerCards.size();
    }
	PPacket packet;
	packet.body() = root.toStyledString();
	packet.pack(GAME_OUT_CARD_BC);

	m_pRoom->Broadcast(packet);

    if (0 == code && find)
    {
        //TO DO
        if (0 == DealCard(card, seat, root))
        {
        }
        else
        {
            code = 0x02;
        }
    }

    return code;
}

int SGSGameLogic::DealCard(int card, int seat, Json::Value& root)
{
    int code = 0;
    m_oLastCard = card;

    switch (m_oLastCard.func())
    {
    case SGSCard::CARD_SHA:
        break;
    case SGSCard::CARD_SHAN:
        break;
    case SGSCard::CARD_TAO:
        break;
    default:
        break;
    }
    ev_timer_stop(g_app.m_pLoop, &play_timer);
    return code;
}

int SGSGameLogic::DealCard_Tao(int seat, int to_seat)
{
    return 0;
}
int SGSGameLogic::DealCard_Sha(int seat, int to_seat)
{
    return 0;
}
int SGSGameLogic::DealCard_Shan(int seat)
{
    int code  = 0;
    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator sga = m_mPlayer.find(seat);
    if (sga != m_mPlayer.end())
    {
        SGSGameAttr &ga = *sga->second;
        Player *self = sga->second->m_player;
        if (ga.m_nToMeCard == SGSCard::CARD_SHA 
        || ga.m_nToMeCard == SGSCard::CARD_WANG_JIAN_QI_FA)
        {
            ga.m_nToMeCard = 0;

            //回到当前的人，看他是否还要继续出牌
        }
        else
        {
            code = 0x02;
        }
    }
    else
    {
        code  = 0x01;
    }

    return code;
}

int SGSGameLogic::ReqDiscard(Player *player)
{
	int code = 0;
	Json::Value root;
	Json::Value result;
	std::string err;

    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator sga = m_mPlayer.find(player->SeatID());

    if (PLAYER_DISCARD == m_nStatus)
    {
        if (sga != m_mPlayer.end())
        {
            if (!Game::ParseMsg(player, &root, err))
            {
                code = 0x01;
            }
            else
            {
                Json::Value &cards = root["cards"];
                if (sga->second->m_nDiscardCnt == (int)cards.size())
                {
                    int i = 0;
                    std::list<std::shared_ptr<SGSCard>> &lstcard = sga->second->m_lstPlayerCards;
                    for (; i < (int)cards.size(); ++i)
                    {
                        for (std::list<std::shared_ptr<SGSCard>>::iterator it = lstcard.begin(); it != lstcard.end();)
                        {
                            if ((*it)->card() == cards[i].asInt())
                            {
                                result["cards"][i] = (*it)->card();
                                it = lstcard.erase(it);
                                break;
                            }
                            else
                            {
                                ++it;
                            }
                        }
                    }
                    if (i != sga->second->m_nDiscardCnt)
                    {
                        code = 0x08;
                    }
                }
                else
                {
                    code = 0x02;
                }
            }
            result["card_cnt"] = sga->second->m_lstPlayerCards.size();
        }
        else
        {
            code = 0x04;
        }
    }
    else
    {
        code = 0x10;
    }
    result["code"] = (code); //
    result["seatid"] = (player->SeatID()); //
	PPacket packet;
	packet.body() = result.toStyledString(); 
	packet.pack(GAME_DISCARD_BC);

    m_pRoom->Broadcast(packet);

    if(0 == code )
    {
        ev_timer_stop(g_app.m_pLoop, &discard_timer);
        PlayCardUC((player->SeatID() + 1) % m_pRoom->m_nMaxPlayerCnt);
    }

    return code;
}
int SGSGameLogic::ReqUseSkill(Player *player)
{
    return 0;
}
int SGSGameLogic::ReqCancelOutCard(Player *player)
{
    int seat = player->SeatID();
    std::map<int, std::shared_ptr<SGSGameAttr>>::iterator sga = m_mPlayer.find(seat);
    if (sga != m_mPlayer.end())
    {
        if (m_nCurrPlayerSeat == seat)
        {
            //弃牌, 当期玩家取消出牌了
        }
    }
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
        root["card_cnt"] = ga.m_lstPlayerCards.size();
        PPacket packet;
        packet.body() = root.toStyledString();
        packet.pack(GAME_DEAL_BC);

        m_pRoom->Unicast(ga.m_player, packet);
    }
    //开始出牌

    PlayCardUC(0);

    return 0;
}

int SGSGameLogic::Deal(SGSGameAttr& ga, Json::Value& v, int cnt) //给player发牌
{
    for (int i = 0; i < cnt; ++i)
    {
        if (0 == m_vCards.size())
        {
            InitCard();
            RandomCard();
        }
        ga.m_lstPlayerCards.push_back(m_vCards.back());
        v["cards"][i] = ga.m_lstPlayerCards.back()->card();
        m_vCards.pop_back();
    }
    v["card_cnt"] = ga.m_lstPlayerCards.size();

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