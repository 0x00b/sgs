#include "sgsgamelogic.h"
#include "../player.h"
#include "../main.h"

SGSGame::SGSGame()
{

}
SGSGame::~SGSGame()
{
}

int SGSGame::Do(Player* player)
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
int SGSGame::GameStart()
{
    return 0;
}