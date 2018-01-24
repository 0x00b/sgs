#include "sgsgameattr.h"
#include "hero.h"

SGSGameAttr::SGSGameAttr():
    m_pHero(std::shared_ptr<Hero>(new Hero()))
{
}
SGSGameAttr::~SGSGameAttr()
{
}