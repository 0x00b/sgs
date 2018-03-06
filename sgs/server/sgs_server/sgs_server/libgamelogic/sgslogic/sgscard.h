/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.24
Description : SGSCard
**************************************************/

#ifndef _SGS_SGS_CARD_H_
#define _SGS_SGS_CARD_H_

#include "../card.h"

class SGSCard: public Card
{
    /*varibles*/
  private:

  protected:
  public:
    static const int CARD_CNT = 108;

    enum CARD_VALUE
    {
      VALLUE_MASK = 0x00000F,
      COLOR_MASK  = 0x0000F0,
      TYPE_MASK   = 0x000F00,
      FUNC_MASK   = 0xFF0000,

      CARD_CLR_BLOCK = 0x000,
      CARD_CLR_HEART = 0x010,
      CARD_CLR_PLUM  = 0x020,
      CARD_CLR_SPADE = 0x030,
    };

    enum CARD_TYPE
    {
      CARD_TYPE_EX            = 0x300,
      
      CARD_SHAN               = 0x00,
      CARD_SHA                = 0x01,
      CARD_TAO                = 0x02,
      CARD_JUE_DOU 			    	= 0x03,
      CARD_WANG_JIAN_QI_FA		= 0x04,
      CARD_TAO_YUAN_JIE_YI		= 0x05,
      CARD_GUO_HE_CHAI_QIAO		= 0x06,
      CARD_SHUN_SHOU_QIAN_YANG= 0x07,
      CARD_WU_ZHONG_SHENG_YOU	= 0x08,
      CARD_JIE_DAO_SHA_REN		= 0x09,
      CARD_WU_GU_FENG_DENG		= 0x0A,
      CARD_NAN_MAN_RU_QIN	  	= 0x0B,
      CARD_WU_XIE_KE_JI		  	= 0x0C,
      CARD_WU_XIE_KE_JI_EX		= 0x0D,
      CARD_LE_BU_SI_SHU		  	= 0x0E,
      CARD_SHAN_DIAN			    = 0x0F,
      CARD_SHAN_DIAN_EX			  = 0x10,
      CARD_ZHU_GE_LIAN_LU	    = 0x11,
      CARD_BA_GUA_ZHEN		    = 0x12,
      CARD_HANG_BING_JIAN	    = 0x13,
      CARD_REN_WANG_DUN		    = 0x14,
      CARD_QING_LONG_YYD	    = 0x15,
      CARD_CI_XIONG_SGJ		    = 0x16,
      CARD_JUE_YING				    = 0x17,
      CARD_QI_LIN_GONG		    = 0x18,
      CARD_CHI_TU 			      = 0x19,
      CARD_DI_LU 			        = 0x1A,
      CARD_GUA_SHI_FU		      = 0x1B,
      CARD_QING_GANG_JIAN     = 0x1C,
      CARD_ZHAN_BA_SHE_MAO    = 0x1D,
      CARD_FANG_TIAN_HUA_J    = 0x1E,
      CARD_DA_WAN 			      = 0x1F,
      CARD_ZHUA_HUANG_FD 	    = 0x20,
      CARD_ZI_XING 			      = 0x21,
    };

    /*functions*/
  public:
    SGSCard(int card, const std::string name = (""), const std::string desc = (""));
    virtual ~SGSCard();
    
    inline virtual int value() const;
    inline virtual int color() const;
    inline virtual int type() const;
    inline virtual int func() const;

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
int SGSCard::func() const
{
  return  (card_ & FUNC_MASK);
}

#endif