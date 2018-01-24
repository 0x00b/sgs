#include "gamelogic.h"


GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::Init(Room *proom)
{
    m_pRoom = proom; 
    m_lstCards = Card::CardList();
}

int GameLogic::Enter(Player *player)
{
    return 0;
}
int GameLogic::Leave(Player *player)
{
    return 0;
}
int GameLogic::GetSeatID(Player *player)
{
    return 0;
}