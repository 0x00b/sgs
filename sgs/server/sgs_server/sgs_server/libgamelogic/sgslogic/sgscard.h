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
    /*functions*/
  public:
    SGSCard(int card, const std::string name = (""), const std::string desc = (""));
    virtual ~SGSCard();

    //must call InitCards() before use this class
    static void InitCards();

    virtual int value() const;
    virtual int color() const;
    virtual int type() const;

  protected:
  
  private:
};

#endif