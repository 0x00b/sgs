#ifndef _SGS_HERO_H_
#define _SGS_HERO_H_

/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.16
Description :
**************************************************/
#include "../../include.h"

enum E_COUNTRY
{
	CTY_WEI = 1,
	CTY_SHU,
	CTY_WU,
	CTY_QUN,
};

enum E_DIFFICUTY
{
	DFCT_EASY = 1,
	DFCT_MID,
	DFCT_DIFFICUT,
};
enum E_SKILL
{
	SKILL_ID = 0,
	SKILL_LIU_BEI_1,/*liu bei skill 1 id*/
	SKILL_LIU_BEI_M,/*liu bei mster skill id*/
	SKILL_SUN_QUAN_1,
	SKILL_SUN_QUAN_M,
	SKILL_CAO_CAO_1,
	SKILL_CAO_CAO_M,
	SKILL_GUAN_YU_1,
	SKILL_ZHANG_FEI_1,
	SKILL_LV_BU_1,
	SKILL_ZHAO_YUN_1,
	SKILL_LV_MENG_1,
	SKILL_XU_CHU_1,
	SKILL_MA_CHAO_1,
	SKILL_MA_CHAO_2,
	SKILL_ZHEN_JI_1,
	SKILL_ZHEN_JI_2,
	SKILL_DA_QIAO_1,
	SKILL_DA_QIAO_2,
	SKILL_HUANG_YUE_YING_1,
	SKILL_HUANG_YUE_YING_2,
	SKILL_DIAO_CAN_1,
	SKILL_DIAO_CAN_2,

};

class Hero
{
public:
	std::string name;
	std::string introduction;
	std::string skill_1_name;
	std::string skill_1_intro;
	std::string skill_2_name;
	std::string skill_2_intro;
	std::string master_skill_name;
	std::string master_skill_intro;
	std::string remark;

	int idhero;
	int country;
	int blood;
	int difficuty;
	int attack;
	int defense;
	int burst;
	int control;
	int assistant;
	int skill_1_id;
	int skill_2_id;
	int master_skill_id;

public:
	Hero();
	~Hero();
};

#endif