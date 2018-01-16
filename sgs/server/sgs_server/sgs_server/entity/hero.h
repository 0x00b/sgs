#ifndef _SGS_HERO_H_
#define _SGS_HERO_H_

/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.16
Description :
**************************************************/
#include "../include.h"

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