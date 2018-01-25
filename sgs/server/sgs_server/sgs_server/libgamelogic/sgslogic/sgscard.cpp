#include "../gameattr.h"
#include "sgscard.h"
#include "sgsgameattr.h"
#include "../gamelogic.h"

/*基本牌*/
#define CT_SHAN		"闪"
#define DESC_CT_SHAN \
"当你受到【杀】的攻击时，你可以使用一张【闪】来抵消【杀】的效果。\n\
　　★闪通常情况下只能在回合外使用或打出。"

#define CT_SHA		"杀"
#define DESC_CT_SHA \
"你的出牌阶段，对除你外，你攻击范围内的一名角色使用，效果是对该角色造成1点伤害。\n\
　　★游戏开始时你的攻击范围是1 。\n\
　　★每个出牌阶段你只能使用一张【杀】。"

#define CT_TAO		"桃"
#define DESC_CT_TAO \
"桃能在两种情况下使用：\n\
1、在你的出牌阶段，你可以使用它来回复你的1点体力。\n\
2、当有角色处于濒死状态时，你可以对该角色使用【桃】，防止该角色的死亡。\n\
　　★例如，一名角色的剩余体力为2点，此时受到【闪电】造成的3点伤害，此时该角色处于濒死状态，该角色或其他任何人合计需使用2张【桃】才能救回（2-3+2=1）。\n\
　　★出牌阶段，若你没有损失体力，你不可以对自己使用【桃】。"

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


#define DESC_CT_JUE_DOU \
"使用目标：除你以外，任意一名角色。\n\
卡牌效果：出牌阶段，对一名其他角色使用；由该角色开始，轮流打出一张【杀】，首先不出【杀】的一方受到另一方造成的一点伤害。"

#define DESC_CT_WANG_JIAN_QI_FA	\
"使用目标：除你以外的所有角色。\n\
卡牌效果：游戏中，必须指定除使用者以外的所有角色为目标，然后他们依次（从你的下家开始）选择是否打出【闪】。"

#define DESC_CT_TAO_YUAN_JIE_YI	\
"卡牌效果：按行动顺序结算，目标角色回复1点体力。"

#define DESC_CT_GUO_HE_CHAI_QIAO \
"使用目标：除你以外，任意一名角色。\n\
卡牌效果：出牌阶段，对一名区域内有牌的其他角色使用。你将其区域内的一张牌弃置。"

#define DESC_CT_SHUN_SHOU_QIAN_YANG	\
"使用目标：除你以外，与你距离1以内的一名角色。\n\
卡牌效果：出牌阶段，对距离为1且区域内有牌的一名其他角色使用。你获得其区域内的一张牌。"

#define DESC_CT_WU_ZHONG_SHENG_YOU	"出牌阶段，对你自己使用，摸两张牌。"

#define DESC_CT_JIE_DAO_SHA_REN	\
"出牌阶段，对除你外，装备区里有武器牌的一名角色A使用，A需对你指定的一名角色B使用一张【杀】，否则你获得A装备区里的武器。\n\
　　★A使用【杀】时，角色技能和武器技能可以照常发动"

#define DESC_CT_WU_GU_FENG_DENG \
"出牌阶段，对所有角色使用。你从牌堆亮出等同于现存角色数量的牌，然后按行动顺序结算～目标角色选择并获得其中的一张。\n\
　　★这张牌会让包括你在内的角色每人各从一定数量的牌里挑选一张加入手牌。"

#define DESC_CT_NAN_MAN_RU_QIN		"南蛮入侵"

#define DESC_CT_WU_XIE_KE_JI \
"在目标锦囊生效前，抵消其对一名角色产生的效果。\n\
　　★【无懈可击】是一张可以在其他锦囊开始结算时使用的锦囊，它只能抵消目标锦囊对一名指定角色产生的效果。\n\
　　★【无懈可击】本身也是锦囊，所以也可以被抵消\n\
　　★特别的，当【无懈可击】抵消【闪电】的效果后，【闪电】不会被弃置，而是继续传递给下家（见【闪电】段落）。"

#define DESC_CT_WU_XIE_KE_JI_EX DESC_CT_WU_XIE_KE_JI

#define DESC_CT_LE_BU_SI_SHU \
"出牌阶段，对除你外，任意一名角色使用，将【乐不思蜀】横置于该角色的判定区里。【乐不思蜀】于该角色的判定阶段开始结算，其效果是：该角色进行一次判定，除非判定结果为红桃，否则跳过其出牌阶段。\n\
　　★若判定结果为红桃则没有事发生。\n\
　　★【乐不思蜀】在结算后都将被弃置。"

#define DESC_CT_SHAN_DIAN \
"出牌阶段，对你使用，将【闪电】横置于你的判定区里。【闪电】于你的下个判定阶段开始结算，其效果是：目标角色进行一次判定，若判定结果为黑桃2～9的牌，则【闪电】对该角色造成3点伤害，弃置【闪电】。若判定结果不在此范围，将【闪电】移动至下家的判定区里。\n\
　　★【闪电】的目标可能会不断的进行改变，直到它生效。若它被抵消，则将它直接移动到下家的判定区里（而不是判定后再移动）。\n\
　　★【闪电】造成的伤害没有来源。"

#define DESC_CT_SHAN_DIAN_EX DESC_CT_SHAN_DIAN

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

#define DESC_CT_ZHU_GE_LIAN_LU  \
"类型：武器\n\
　　攻击范围：1\n\
　　作用：出牌阶段，你可以使用任意张【杀】"

#define DESC_CT_BA_GUA_ZHEN	\
"类型：防具\n\
　　作用：每当你需要使用（或打出）一张【闪】时，你可以进行一次判定：若结果为红色，则视为你使用（或打出）了一张【闪】；若为黑色，则你仍可以从手牌里使用（或打出）。\n\
　　★由八卦使用或打出的闪，并非从你的手牌中使用或打出。"

#define DESC_CT_HANG_BING_JIAN \
"类型：武器\n\
　　攻击范围：2\n\
　　作用：当你使用【杀】造成伤害时，你可以防止此伤害，改为弃置该目标角色的两张牌。\n\
　　★弃对方两张牌时,可以是手牌也可以是已装备的牌。（相当于两张【过河拆桥】的效果）。\n\
　　★弃完第一张，再弃第二张。\n\
　　★不得弃掉对方判定区里的牌。"

#define DESC_CT_REN_WANG_DUN \
"类型：防具\n\
　　作用：锁定技，黑色的【杀】对你无效。\n\
　　★【决斗】过程中【仁王盾】无效。"

#define DESC_CT_QING_LONG_YYD \
"类型：武器\n\
　　攻击范围：3\n\
　　作用：当你使用的【杀】被【闪】抵消时，你可以立即对相同的目标再使用一张【杀】，直到【杀】生效或你不愿意出了为止。"

#define DESC_CT_CI_XIONG_SGJ \
"类型：武器\n\
　　攻击范围：2\n\
　　作用：你使用【杀】，指定了一名异性角色为目标后，在【杀】结算前，你可以令对方选择一项：自己弃一张手牌或者让你从牌堆摸一张牌。"

#define DESC_CT_JUE_YING	"《三国志 魏书》：“公所乘马名绝影，为流矢所中，伤颊及足，并中公右臂。世语曰：昂不能骑，进马于公，公故免，而昂遇害”。"
#define DESC_CT_QI_LIN_GONG	\
"类型：武器\n\
　　攻击范围：5\n\
　　作用：你使用【杀】对目标角色造成伤害时，你可以将其装备区里的一匹马弃置。"

#define DESC_CT_CHI_TU	"《三国志 魏志 吕布传》：“布有良马名曰赤兔。"
#define DESC_CT_DI_LU	"《三国志 蜀志 先主备传》：“所乘马名的卢，骑的卢走，堕襄阳城西檀溪水中，溺不得出。备急曰：‘的卢，今日危矣，可努力。’的卢乃一踊三丈，遂得过。"

#define DESC_CT_GUA_SHI_FU	\
"类型：武器\n\
　　攻击范围：3\n\
　　作用：目标角色使用【闪】抵消你使用【杀】的效果时，你可以弃两张牌，则【杀】依然造成伤害。"

#define DESC_CT_QING_GANG_JIAN \
"类型：武器\n\
　　攻击范围：2\n\
　　作用：锁定技，每当你使用【杀】攻击一名角色时，无视该角色的防具。\n\
　　★对方的防具没有任何效果。"

#define DESC_CT_ZHAN_BA_SHE_MAO \
"类型：武器\n\
　　攻击范围：3\n\
　　作用：当你需要使用（或打出）一张【杀】时，你可以将两张手牌当一张【杀】使用（或打出）。"

#define DESC_CT_FANG_TIAN_HUA_J \
"类型：武器\n\
　　攻击范围：4\n\
　　作用：当你使用的【杀】是你的最后一张手牌时，你可以为这张【杀】指定至多三名目标角色，然后按行动顺序结算之。"

#define DESC_CT_DA_WAN 			 	"宋司马光《天马歌》：“大宛汗血古共知，青海龙种骨更奇，网丝旧画昔尝见，不意人间今见之。"
#define DESC_CT_ZHUA_HUANG_FD 	 	"《三国演义》：“曹操骑爪黄飞电马，引十万之众，与天子猎于许田。”"
#define DESC_CT_ZI_XING 		 	"《魏志》陈思王表文帝曰：“臣于武皇帝世得大宛紫骍马一匹，教令习拜。"

#define SH_SGS_CARD(card, name, desc) (std::shared_ptr<Card>((Card*)new SGSCard((card), (name), (desc))))

const std::shared_ptr<Card>* const GameLogic::g_lstCards = new std::shared_ptr<Card>[SGSCard::CARD_CNT]
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
	/*方块*/SH_SGS_CARD(0x203, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG),
	/*梅花*/SH_SGS_CARD(0x113, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x213, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*红桃*/SH_SGS_CARD(0x123, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x223, CT_WU_GU_FENG_DENG	,DESC_CT_WU_GU_FENG_DENG),
	/*黑桃*/SH_SGS_CARD(0x133, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*黑桃*/SH_SGS_CARD(0x233, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG),
	/*4*/
	/*方块*/SH_SGS_CARD(0x104, CT_SHAN				,DESC_CT_SHAN),
	/*方块*/SH_SGS_CARD(0x204, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG),
	/*梅花*/SH_SGS_CARD(0x114, CT_SHA				,DESC_CT_SHA),
	/*梅花*/SH_SGS_CARD(0x214, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*红桃*/SH_SGS_CARD(0x124, CT_TAO				,DESC_CT_TAO),
	/*红桃*/SH_SGS_CARD(0x224, CT_WU_GU_FENG_DENG	,DESC_CT_WU_GU_FENG_DENG),
	/*黑桃*/SH_SGS_CARD(0x134, CT_GUO_HE_CHAI_QIAO	,DESC_CT_GUO_HE_CHAI_QIAO),
	/*黑桃*/SH_SGS_CARD(0x234, CT_SHUN_SHOU_QIAN_YANG,DESC_CT_SHUN_SHOU_QIAN_YANG),
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
	/*黑桃*/SH_SGS_CARD(0x13B, CT_SHUN_SHOU_QIAN_YANG, DESC_CT_SHUN_SHOU_QIAN_YANG),
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



SGSCard::SGSCard(int card, const std::string name, const std::string desc) : Card(card, name, desc)
{

}
SGSCard::~SGSCard()
{
}

