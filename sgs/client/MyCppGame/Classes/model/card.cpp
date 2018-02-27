#include "card.h"

Card::Card(int card, const std::string name, const std::string desc) : 
  card_(card),
  name_(name),
  desc_(desc)
{
}

Card::~Card()
{
}

const std::string &Card::desc() const
{
  return desc_;
}

const std::string &Card::name() const
{
  return name_;
}

const int &Card::card() const
{
  return card_;
}


int Card::type() const
{
  return 0;
}
