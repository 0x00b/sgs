#include "sgsgamelogic.h"
#include "../../player.h"
#include "../../main.h"

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