/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.24
Description : SGSCard
**************************************************/

#ifndef _SGS_SGS_CARD_H_
#define _SGS_SGS_CARD_H_

#include "../card.h"

class SGSCard: private Card
{
    /*varibles*/
  private:

  protected:
  public:
    static const int CARD_CNT = 108;

    enum CARD_VALUE
    {
      VALLUE_MASK = 0x00F,
      COLOR_MASK  = 0x0F0,
      TYPE_MASK   = 0xF00,
    };

    enum CARD_TYPE
    {
      CARD_TYPE_EX = 0x300,
    };

    enum CARD_COLOR
    {
      CARD_CLR_BLOCK = 0x000,
      CARD_CLR_HEART = 0x010,
      CARD_CLR_PLUM  = 0x020,
      CARD_CLR_SPADE = 0x030,
    };
    /*functions*/
  public:
    SGSCard(int card, const std::string name = (""), const std::string desc = (""));
    virtual ~SGSCard();
    
    inline virtual int value() const;
    inline virtual int color() const;
    inline virtual int type() const;

  protected:
  
  private:
};



int SGSCard::value() const
{
	return (card_ & VALLUE_MASK);
}
int SGSCard::color() const
{
	return (card_ & COLOR_MASK);
}
int SGSCard::type() const
{
	return (card_ & TYPE_MASK);
}

#endif