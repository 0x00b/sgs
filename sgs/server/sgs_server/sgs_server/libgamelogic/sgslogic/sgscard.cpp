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

#define DESC_CT_SHAN			"闪"
#define DESC_CT_SHA				"杀"
#define DESC_CT_TAO				"桃"

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
#define CT_WU_XIE_KE_JI			"无懈可击"
#define CT_WU_XIE_KE_JI_EX		"无懈可击(EX)"
#define CT_LE_BU_SI_SHU			"乐不思蜀"
#define CT_SHAN_DIAN			"闪电"
#define CT_SHAN_DIAN_EX			"闪电(EX)"

#define DESC_CT_JUE_DOU 			"决斗"
#define DESC_CT_WANG_JIAN_QI_FA		"万箭齐发"
#define DESC_CT_TAO_YUAN_JIE_YI		"桃源结义"
#define DESC_CT_GUO_HE_CHAI_QIAO	"过河拆桥"
#define DESC_CT_SHUN_SHOU_QIAN_YANG	"顺手牵羊"
#define DESC_CT_WU_ZHONG_SHENG_YOU	"无中生有"
#define DESC_CT_JIE_DAO_SHA_REN		"借刀杀人"
#define DESC_CT_WU_GU_FENG_DENG		"五谷丰登"
#define DESC_CT_NAN_MAN_RU_QIN		"南蛮入侵"
#define DESC_CT_WU_XIE_KE_JI		"无懈可击"
#define DESC_CT_WU_XIE_KE_JI_EX		"无懈可击(EX)"
#define DESC_CT_LE_BU_SI_SHU		"乐不思蜀"
#define DESC_CT_SHAN_DIAN			"闪电"
#define DESC_CT_SHAN_DIAN_EX		"闪电(EX)"

/*装备牌*/
#define CT_ZHU_GE_LIAN_LU		"诸葛连弩(1)"
#define CT_BA_GUA_ZHEN			"八卦阵"
#define CT_HANG_BING_JIAN		"寒冰剑(2)(EX)"
#define CT_REN_WANG_DUN			"仁王盾(EX)"
#define CT_QING_LONG_YYD		"青龙偃月刀(3)"
#define CT_CI_XIONG_SGJ			"雌雄双股剑(2)"
#define CT_JUE_YING				"绝影(+1)"
#define CT_QI_LIN_GONG			"麒麟弓(5)"
#define CT_CHI_TU 			 	"赤兔(-1)"
#define CT_DI_LU 			 	"的卢(+1)"
#define CT_GUA_SHI_FU			"贯石斧(3)"
#define CT_QING_GANG_JIAN 	 	"青釭剑(2)"
#define CT_ZHAN_BA_SHE_MAO 	 	"丈八蛇矛(3)"
#define CT_FANG_TIAN_HUA_J  	"方天画戟(4)"
#define CT_DA_WAN 			 	"大宛(-1)"
#define CT_ZHUA_HUANG_FD 	 	"爪黄飞电(+1)"
#define CT_ZI_XING 			 	"紫骍(-1)"

#define DESC_CT_ZHU_GE_LIAN_LU		"诸葛连弩(1)"
#define DESC_CT_BA_GUA_ZHEN			"八卦阵"
#define DESC_CT_HANG_BING_JIAN		"寒冰剑(2)(EX)"
#define DESC_CT_REN_WANG_DUN		"仁王盾(EX)"
#define DESC_CT_QING_LONG_YYD		"青龙偃月刀(3)"
#define DESC_CT_CI_XIONG_SGJ		"雌雄双股剑(2)"
#define DESC_CT_JUE_YING			"绝影(+1)"
#define DESC_CT_QI_LIN_GONG			"麒麟弓(5)"
#define DESC_CT_CHI_TU 			 	"赤兔(-1)"
#define DESC_CT_DI_LU 			 	"的卢(+1)"
#define DESC_CT_GUA_SHI_FU			"贯石斧(3)"
#define DESC_CT_QING_GANG_JIAN 	 	"青釭剑(2)"
#define DESC_CT_ZHAN_BA_SHE_MAO  	"丈八蛇矛(3)"
#define DESC_CT_FANG_TIAN_HUA_J  	"方天画戟(4)"
#define DESC_CT_DA_WAN 			 	"大宛(-1)"
#define DESC_CT_ZHUA_HUANG_FD 	 	"爪黄飞电(+1)"
#define DESC_CT_ZI_XING 		 	"紫骍(-1)"


static const std::shared_ptr<Card> g_sgsCards[SGSCard::CARD_CNT] =
{
	/*A*/
	/*方块*/SH_SGS_CARD(0x101, CT_JUE_DOU			,DESC_CT_JUE_DOU),
	/*方块*/SH_SGS_CARD(0x201, CT_ZHU_GE_LIAN_LU	,DESC_CT_ZHU_GE_LIAN_LU),
	/*梅花*/SH_SGS_CARD(0x111, CT_JUE_DOU			,DESC_CT_JUE_DOU),
	/*梅花*/SH_SGS_CARD(0x211, CT_ZHU_GE_LIAN_LU	,DESC_CT_ZHU_GE_LIAN_LU),
	/*红桃*/SH_SGS_CARD(0x121, CT_WANG_JIAN_QI_FA	,DESC_CT_WANG_JIAN_QI_FA),
	/*红桃*/SH_SGS_CARD(0x221, CT_TAO_YUAN_JIE_YI	,DESC_CT_TAO_YUAN_JIE_YI),
	/*黑桃*/SH_SGS_CARD(0x131, CT_JUE_DOU			,DESC_CT_JUE_DOU),
	/*黑桃*/SH_SGS_CARD(0x231, CT_SHAN_DIAN			,DESC_CT_SHAN_DIAN),
	/*2*/											 
	/*方块*/SH_SGS_CARD(0x102, CT_SHAN				,DESC_CT_SHAN),
	/*方块*/SH_SGS_CARD(0x202, CT_SHAN				,DESC_CT_SHAN),
	/*梅花*/SH_SGS_CARD(0x112, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x212, CT_BA_GUA_ZHEN		,DESC_CT_BA_GUA_ZHEN),
	/*红桃*/SH_SGS_CARD(0x122, CT_SHAN				,DESC_CT_SHAN),
	/*红桃*/SH_SGS_CARD(0x222, CT_SHAN				,DESC_CT_SHAN),
	/*黑桃*/SH_SGS_CARD(0x132, CT_BA_GUA_ZHEN		,DESC_CT_BA_GUA_ZHEN),
	/*黑桃*/SH_SGS_CARD(0x232, CT_CI_XIONG_SGJ		,DESC_CT_CI_XIONG_SGJ),
	/*3*/											 
	/*方块*/SH_SGS_CARD(0x103, CT_SHAN				,DESC_CT_SHAN),
	/*方块*/SH_SGS_CARD(0x203, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG,),
	/*梅花*/SH_SGS_CARD(0x113, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x213, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*红桃*/SH_SGS_CARD(0x123, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x223, CT_WU_GU_FENG_DENG	,DESC_CT_WU_GU_FENG_DENG),
	/*黑桃*/SH_SGS_CARD(0x133, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*黑桃*/SH_SGS_CARD(0x233, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG,),
	/*4*/
	/*方块*/SH_SGS_CARD(0x104, CT_SHAN				,DESC_CT_SHAN),
	/*方块*/SH_SGS_CARD(0x204, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG,),
	/*梅花*/SH_SGS_CARD(0x114, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x214, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*红桃*/SH_SGS_CARD(0x124, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x224, CT_WU_GU_FENG_DENG	,DESC_CT_WU_GU_FENG_DENG),
	/*黑桃*/SH_SGS_CARD(0x134, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*黑桃*/SH_SGS_CARD(0x234, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG,),
	/*5*/
	/*方块*/SH_SGS_CARD(0x105, CT_SHAN				,DESC_CT_SHAN),
	/*方块*/SH_SGS_CARD(0x205, CT_GUA_SHI_FU		,DESC_CT_GUA_SHI_FU),
	/*梅花*/SH_SGS_CARD(0x115, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x215, CT_DI_LU				,DESC_CT_DI_LU),
	/*红桃*/SH_SGS_CARD(0x125, CT_QI_LIN_GONG		,DESC_CT_QI_LIN_GONG),
	/*红桃*/SH_SGS_CARD(0x225, CT_CHI_TU			,DESC_CT_CHI_TU),
	/*黑桃*/SH_SGS_CARD(0x135, CT_QING_LONG_YYD		,DESC_CT_QING_LONG_YYD),
	/*黑桃*/SH_SGS_CARD(0x235, CT_JUE_YING			,DESC_CT_JUE_YING),
	/*6*/											 
	/*方块*/SH_SGS_CARD(0x106, CT_SHA				,DESC_CT_SHA),
	/*方块*/SH_SGS_CARD(0x206, CT_SHAN				,DESC_CT_SHAN),
	/*梅花*/SH_SGS_CARD(0x116, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x216, CT_LE_BU_SI_SHU		,DESC_CT_LE_BU_SI_SHU),
	/*红桃*/SH_SGS_CARD(0x126, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x226, CT_LE_BU_SI_SHU		,DESC_CT_LE_BU_SI_SHU),
	/*黑桃*/SH_SGS_CARD(0x136, CT_LE_BU_SI_SHU		,DESC_CT_LE_BU_SI_SHU),
	/*黑桃*/SH_SGS_CARD(0x236, CT_QING_GANG_JIAN	,DESC_CT_QING_GANG_JIAN),
	/*7*/											 
	/*方块*/SH_SGS_CARD(0x107, CT_SHA				,DESC_CT_SHA),
	/*方块*/SH_SGS_CARD(0x207, CT_SHAN				,DESC_CT_SHAN),
	/*梅花*/SH_SGS_CARD(0x117, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x217, CT_NAN_MAN_RU_QIN	,DESC_CT_NAN_MAN_RU_QIN),
	/*红桃*/SH_SGS_CARD(0x127, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x227, CT_WU_ZHONG_SHENG_YOU,DESC_CT_WU_ZHONG_SHENG_YOU),
	/*黑桃*/SH_SGS_CARD(0x137, CT_SHA				,DESC_CT_SHA),
	/*黑桃*/SH_SGS_CARD(0x237, CT_NAN_MAN_RU_QIN	,DESC_CT_NAN_MAN_RU_QIN),
	/*8*/											 
	/*方块*/SH_SGS_CARD(0x108, CT_SHA				,DESC_CT_SHA),
	/*方块*/SH_SGS_CARD(0x208, CT_SHAN				,DESC_CT_SHAN),
	/*梅花*/SH_SGS_CARD(0x118, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x218, CT_SHA				,DESC_CT_SHA),
	/*红桃*/SH_SGS_CARD(0x128, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x228, CT_WU_ZHONG_SHENG_YOU,DESC_CT_WU_ZHONG_SHENG_YOU),
	/*黑桃*/SH_SGS_CARD(0x138, CT_SHA				,DESC_CT_SHA),
	/*黑桃*/SH_SGS_CARD(0x238, CT_SHA				,DESC_CT_SHA),
	/*9*/											 
	/*方块*/SH_SGS_CARD(0x109, CT_SHA				,DESC_CT_SHA),
	/*方块*/SH_SGS_CARD(0x209, CT_SHAN				,DESC_CT_SHAN),
	/*梅花*/SH_SGS_CARD(0x119, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x219, CT_SHA				,DESC_CT_SHA),
	/*红桃*/SH_SGS_CARD(0x129, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x229, CT_WU_ZHONG_SHENG_YOU,DESC_CT_WU_ZHONG_SHENG_YOU),
	/*黑桃*/SH_SGS_CARD(0x139, CT_SHA				,DESC_CT_SHA),
	/*黑桃*/SH_SGS_CARD(0x239, CT_SHA				,DESC_CT_SHA),
	/*10*/											 
	/*方块*/SH_SGS_CARD(0x10A, CT_SHA				,DESC_CT_SHA),
	/*方块*/SH_SGS_CARD(0x20A, CT_SHAN				,DESC_CT_SHAN),
	/*梅花*/SH_SGS_CARD(0x11A, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x21A, CT_SHA				,DESC_CT_SHA),
	/*红桃*/SH_SGS_CARD(0x12A, CT_SHA				,DESC_CT_SHA),
	/*红桃*/SH_SGS_CARD(0x22A, CT_SHA				,DESC_CT_SHA),
	/*黑桃*/SH_SGS_CARD(0x13A, CT_SHA				,DESC_CT_SHA),
	/*黑桃*/SH_SGS_CARD(0x23A, CT_SHA				,DESC_CT_SHA),
	/*J*/											 
	/*方块*/SH_SGS_CARD(0x10B, CT_SHAN				,DESC_CT_SHAN),
	/*方块*/SH_SGS_CARD(0x20B, CT_SHAN				,DESC_CT_SHAN),
	/*梅花*/SH_SGS_CARD(0x11B, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x21B, CT_SHA				,DESC_CT_SHA),
	/*红桃*/SH_SGS_CARD(0x12B, CT_SHA				,DESC_CT_SHA),
	/*红桃*/SH_SGS_CARD(0x22B, CT_WU_ZHONG_SHENG_YOU,DESC_CT_WU_ZHONG_SHENG_YOU),
	/*黑桃*/SH_SGS_CARD(0x13B, CT_SHUN_SHOU_QIAN_YANG, DESC_CT_SHUN_SHOU_QIAN_YANG,),
	/*黑桃*/SH_SGS_CARD(0x23B, CT_WU_XIE_KE_JI		,DESC_CT_WU_XIE_KE_JI),
	/*Q*/											 
	/*方块*/SH_SGS_CARD(0x10C, CT_TAO				,DESC_CT_TAO),
	/*方块*/SH_SGS_CARD(0x20C, CT_FANG_TIAN_HUA_J	,DESC_CT_FANG_TIAN_HUA_J),
	/*梅花*/SH_SGS_CARD(0x11C, CT_JIE_DAO_SHA_REN	,DESC_CT_JIE_DAO_SHA_REN),
	/*梅花*/SH_SGS_CARD(0x21C, CT_WU_XIE_KE_JI		,DESC_CT_WU_XIE_KE_JI),
	/*红桃*/SH_SGS_CARD(0x12C, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x22C, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*黑桃*/SH_SGS_CARD(0x13C, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*黑桃*/SH_SGS_CARD(0x23C, CT_ZHAN_BA_SHE_MAO	,DESC_CT_ZHAN_BA_SHE_MAO),
	/*K*/											 
	/*方块*/SH_SGS_CARD(0x10D, CT_SHA				,DESC_CT_SHA),
	/*方块*/SH_SGS_CARD(0x20D, CT_ZI_XING			,DESC_CT_ZI_XING),
	/*梅花*/SH_SGS_CARD(0x11D, CT_JIE_DAO_SHA_REN	,DESC_CT_JIE_DAO_SHA_REN),
	/*梅花*/SH_SGS_CARD(0x21D, CT_WU_XIE_KE_JI		,DESC_CT_WU_XIE_KE_JI),
	/*红桃*/SH_SGS_CARD(0x12D, CT_SHAN				,DESC_CT_SHAN),
	/*红桃*/SH_SGS_CARD(0x22D, CT_ZHUA_HUANG_FD		,DESC_CT_ZHUA_HUANG_FD),
	/*黑桃*/SH_SGS_CARD(0x13D, CT_NAN_MAN_RU_QIN	,DESC_CT_NAN_MAN_RU_QIN),
	/*黑桃*/SH_SGS_CARD(0x23D, CT_DA_WAN			,DESC_CT_DA_WAN),
	/*EX*/
	/*方块Q*/SH_SGS_CARD(0x30C, CT_WU_XIE_KE_JI_EX	, DESC_CT_WU_XIE_KE_JI_EX),
	/*红桃Q*/SH_SGS_CARD(0x32C, CT_SHAN_DIAN_EX		, DESC_CT_SHAN_DIAN_EX),
	/*梅花2*/SH_SGS_CARD(0x312, CT_REN_WANG_DUN		, DESC_CT_REN_WANG_DUN),
	/*黑桃2*/SH_SGS_CARD(0x332, CT_HANG_BING_JIAN	, DESC_CT_HANG_BING_JIAN),

};

SGSCard::SGSCard(int card, const std::string name, const std::string desc) : Card(card, name, desc)
{

}
SGSCard::~SGSCard()
{
}

