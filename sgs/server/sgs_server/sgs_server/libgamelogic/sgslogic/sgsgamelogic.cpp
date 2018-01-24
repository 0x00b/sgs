#include "sgsgamelogic.h"
#include "sgsgameattr.h"
#include "../../include.h"
#include "../../player.h"
#include "../../main.h"
#include "../../room.h"

SGSGameLogic::SGSGameLogic()
{

}
SGSGameLogic::~SGSGameLogic()
{
}

int SGSGameLogic::Do(Player* player)
{
    if (NULL != player)
    {
        switch(player->m_iClient.m_iPacket.header.cmd)
        {
        case GAME_START:
            break;
        default:
            break;
        }
    }
    return 0;
}
int SGSGameLogic::GameStart()
{
    return 0;
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
                    m_mPlayer.insert(std::pair<Player *, std::shared_ptr<GameAttr>>(player, (gm_attr)));
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
    }

    return nRet;
    //
}