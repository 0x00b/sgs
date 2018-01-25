#include "../card.h"
#include "../gameattr.h"
#include "sgscard.h"
#include "sgsgameattr.h"


static const int g_cbCards[SGSCard::CARD_CNT] = {
//  A      2      3      4      5      6      7      8      9      10     J      Q		K      --
	0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107, 0x108, 0x109, 0x10A, 0x10B, 0x10C, 0x10D, // 方块A2--K
	0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x118, 0x119, 0x11A, 0x11B, 0x11C, 0x11D, // 梅花A2--K
	0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 0x128, 0x129, 0x12A, 0x12B, 0x12C, 0x12D, // 红桃A2--K
	0x131, 0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139, 0x13A, 0x13B, 0x13C, 0x13D, // 黑桃A2--K
	0x201, 0x202, 0x203, 0x204, 0x205, 0x206, 0x207, 0x208, 0x209, 0x20A, 0x20B, 0x20C, 0x20D, // A2--K
	0x211, 0x212, 0x213, 0x214, 0x215, 0x216, 0x217, 0x218, 0x219, 0x21A, 0x21B, 0x21C, 0x21D, // A2--K
	0x221, 0x222, 0x223, 0x224, 0x225, 0x226, 0x227, 0x228, 0x229, 0x22A, 0x22B, 0x22C, 0x22D, // A2--K
	0x231, 0x232, 0x233, 0x234, 0x235, 0x236, 0x237, 0x238, 0x239, 0x23A, 0x23B, 0x23C, 0x23D, // A2--K
	0x312, 0x332,																			   //ex
	0x30C, 0x32C,																			   //ex
};

#define SH_SGS_CARD(card, name, desc) (std::shared_ptr<Card>(new SGSCard((card), (name), (desc))))

/*基本牌*/
#define CT_SHAN					"闪"
#define CT_SHA					"杀"
#define CT_TAO					"桃"

/*锦囊牌*/	
#define CT_JUE_DOU 				"决斗"
#define CT_WANG_JIAN_QI_FA		"万箭齐发"
#define CT_TAO_YUAN_JIE_YI		"桃源结义"
#define CT_GUO_HE_CHAI_QIAO		"过河拆桥"
#define CT_SHUN_SHOU_QIAN_YANG	"顺手牵羊"
#define CT_WU_ZHONG_SHENG_YOU	"无中生有"
#define CT_JIE_DAO_SHA_REN		"借刀杀人"
#define CT_WU_GU_FENG_DENG		"五谷丰登"
#define CT_NAN_MAN_RU_QIN		"南蛮入侵"
#define CT_WU_XIE_KE_JI			"无懈可击
#define CT_LE_BU_SI_SHU			"乐不思蜀"
#define CT_SHAN_DIAN			"闪电"

/*装备牌*/
#define CT_ZHU_GE_LIAN_LU 	"诸葛连弩(1)"
#define CT_ 			 	"八卦阵"
#define CT_ 			 	"寒冰剑(2)(EX)"
#define CT_ 			 	"仁王盾(EX)"
#define CT_ 			 	"青龙"
#define CT_ 			 	"八卦阵"
#define CT_ 			 	"八卦阵"
#define CT_ 			 	"八卦阵"
#define CT_ 			 	"八卦阵"
#define CT_ 			 	"八卦阵"
#define CT_ 			 	"八卦阵"


static const std::shared_ptr<Card> g_sgsCards[SGSCard::CARD_CNT] =
	{
		/*A*/
		/*方块*/SH_SGS_CARD(0x101, CT_JUE_DOU, ""),
		/*方块*/SH_SGS_CARD(0x201, CT_ZHU_GE_LIAN_LU, ""),
		/*梅花*/SH_SGS_CARD(0x111, CT_JUE_DOU, ""),
		/*梅花*/SH_SGS_CARD(0x211, CT_ZHU_GE_LIAN_LU, ""),
		/*红桃*/SH_SGS_CARD(0x121, CT_WANG_JIAN_QI_FA, ""),
		/*红桃*/SH_SGS_CARD(0x221, CT_TAO_YUAN_JIE_YI, ""),
		/*黑桃*/SH_SGS_CARD(0x131, CT_JUE_DOU, ""),
		/*黑桃*/SH_SGS_CARD(0x231, CT_SHAN_DIAN, ""),

		/*2*/
		/*方块*/SH_SGS_CARD(0x102, "闪", ""),
		/*方块*/SH_SGS_CARD(0x202, "闪", ""),
		/*梅花*/SH_SGS_CARD(0x112, "决斗", ""),
		/*梅花*/SH_SGS_CARD(0x212, "诸葛连弩(1)", ""),
		/*红桃*/SH_SGS_CARD(0x122, "万箭齐发", ""),
		/*红桃*/SH_SGS_CARD(0x222, "桃源结义", ""),
		/*黑桃*/SH_SGS_CARD(0x132, "决斗", ""),
		/*黑桃*/SH_SGS_CARD(0x232, "闪电", ""),

};

SGSCard::SGSCard(int card, const std::string name, const std::string desc) : Card(card, name, desc)
{ 

}
SGSCard::~SGSCard()
{
}

void SGSCard::InitCards()
{
	g_lstCards.clear();
	for (int i = 0; i < CARD_CNT; ++i)
	{
		g_lstCards.push_back(g_sgsCards[i]);
	}
}
