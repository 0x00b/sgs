#include "gamelogic.h"
#include "gameattr.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::Init(Room *proom)
{
    m_pRoom = proom; 
    m_lstCards = g_lstCards;
}

int GameLogic::Leave(Player *player)
{
    m_mPlayer.erase(player);

    return 0;
}

int GameLogic::GetSeatID(Player *player)
{
    std::map<Player*, std::shared_ptr<GameAttr>>::iterator it_player = m_mPlayer.find(player);

    if(m_mPlayer.end() != it_player)
    {
        return it_player->second->m_nSeatId;
    }

    return -1;
}