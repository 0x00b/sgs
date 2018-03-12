#include "sgsgameattr.h"
#include "hero.h"
#include "sgscard.h"

SGSGameAttr::SGSGameAttr():
    //m_pHero(new Hero()),
    m_nToMeCard(SGSCard::CARD_NONE),
    m_bSelectedHero(false)
{
}
SGSGameAttr::~SGSGameAttr()
{
}

void SGSGameAttr::Reset()
{
}