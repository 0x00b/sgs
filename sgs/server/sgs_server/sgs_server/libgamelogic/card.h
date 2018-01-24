/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.24
Description : Card
**************************************************/

#ifndef _SGS_CARD_H_
#define _SGS_CARD_H_

#include <string>
#include <memory>
#include <list>

class Card
{
    /*varibles*/
  private:

  protected:

    int card_;        //value
    std::string name_; //desciption
    std::string desc_; //desciption
    
  public:
    /*functions*/
  public:
    Card(int card, const std::string name = (""), const std::string desc = (""));
    virtual ~Card();

    virtual const int &card() const;
    virtual const std::string &desc() const;
    virtual const std::string &name() const;

    virtual int value() const = 0;
    virtual int color() const = 0;
    virtual int type() const;

  protected:
  private:
};

#endif