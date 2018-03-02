#include "hero.h"
#include "../../mysqlutil/mysqlutil.h"
#include "../../log.h"
#include "../../app.h"

std::vector<std::shared_ptr<Hero>> Hero::g_Heros;

Hero::Hero():
	idhero(0),
	country(0),
	blood(0),
	difficuty(0),
	attack(0),
	defense(0),
	burst(0),
	control(0),
	assistant(0),
	skill_1_id(0),
	skill_2_id(0),
	master_skill_id(0),
    role(ROLE_NONE)
{
}

Hero::~Hero()
{
}


/*
| Field              | Type         | Null | Key | Default | Extra          |
+--------------------+--------------+------+-----+---------+----------------+
| idhero             | int(11)      | NO   | PRI | NULL    | auto_increment |
| name               | varchar(45)  | YES  |     | NULL    |                |
| country            | int(11)      | YES  |     | NULL    |                |
| blood              | int(11)      | YES  |     | NULL    |                |
| introduction       | varchar(512) | YES  |     | NULL    |                |
| difficuty          | int(11)      | YES  |     | 0       |                |
| attack             | int(11)      | YES  |     | 0       |                |
| defense            | int(11)      | YES  |     | 0       |                |
| burst              | int(11)      | YES  |     | 0       |                |
| control            | int(11)      | YES  |     | 0       |                |
| assistant          | int(11)      | YES  |     | 0       |                |
| skill_1_id         | int(11)      | YES  |     | NULL    |                |
| skill_1_name       | varchar(45)  | YES  |     | NULL    |                |
| skill_1_intro      | varchar(512) | YES  |     | NULL    |                |
| skill_2_id         | int(11)      | YES  |     | NULL    |                |
| skill_2_name       | varchar(45)  | YES  |     | NULL    |                |
| skill_2_intro      | varchar(512) | YES  |     | NULL    |                |
| master_skill_id    | int(11)      | YES  |     | NULL    |                |
| master_skill_name  | varchar(45)  | YES  |     | NULL    |                |
| master_skill_intro | varchar(512) | YES  |     | NULL    |                |
| remark             | varchar(45)  | YES  |     | NULL    |                |
+--------------------+--------------+------+-----+---------+----------------+
SELECT `hero`.`idhero`,                                                                                                                                           │
`hero`.`name`,                                                                                                                                                           │
`hero`.`country`,                                                                                                                                                │
`hero`.`blood`,                                                                                                                                                  │
`hero`.`introduction`,                                                                                                                                           │
`hero`.`difficuty`,                                                                                                                                              │
`hero`.`attack`,                                                                                                                                                 │
`hero`.`defense`,                                                                                                                                                │
`hero`.`burst`                                                                                                                                                   │
`hero`.`control`,                                                                                                                                                │
`hero`.`assistant`,                                                                                                                                              │
`hero`.`skill_1_id`,                                                                                                                                             │
`hero`.`skill_1_name`,                                                                                                                                           │
`hero`.`skill_1_intro`,                                                                                                                                          │
`hero`.`skill_2_id`,                                                                                                                                             │
`hero`.`skill_2_name`,                                                                                                                                           │
`hero`.`skill_2_intro`                                                                                                                                           │
`hero`.`master_skill_id`,                                                                                                                                        │
`hero`.`master_skill_name`,                                                                                                                                      │
`hero`.`master_skill_intro`,                                                                                                                                     │
`hero`.`remark`                                                                                                                                                  │
 FROM `sgs_db`.`hero`;
*/
int Hero::GetALLhero()
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string sql = "SELECT `hero`.`idhero`,"
		"`hero`.`name`,"
		"`hero`.`country`,"
		"`hero`.`blood`,"
		"`hero`.`introduction`,"
		"`hero`.`difficuty`,"
		"`hero`.`attack`,"
		"`hero`.`defense`,"
		"`hero`.`burst`,"
		"`hero`.`control`,"
		"`hero`.`assistant`,"
		"`hero`.`skill_1_id`,"
		"`hero`.`skill_1_name`,"
		"`hero`.`skill_1_intro`,"
		"`hero`.`skill_2_id`,"
		"`hero`.`skill_2_name`,"
		"`hero`.`skill_2_intro`,"
		"`hero`.`master_skill_id`,"
		"`hero`.`master_skill_name`,"
		"`hero`.`master_skill_intro`,"
		"`hero`.`remark`"
		" FROM `sgs_db`.`hero`"
		;

	sgslog.debug(FFL_s_s,"sql:",sql.c_str());

	int nRet = 0;
	if ((nRet = MySqlUtil::MysqlQuery(res, sql.c_str())))
	{
        g_Heros.clear();
		int j = mysql_num_fields(res);
		while ((row = mysql_fetch_row(res)))
		{
            Hero* hero = new Hero();
            g_Heros.push_back(std::shared_ptr<Hero>(hero));
			for (int i = 0; i < j; i++)
			{
				if (row[i] == NULL)
				{
					continue;
				}
				switch (i)
				{
				case 0:
					hero->idhero = atoi(row[i]); break;
				case 1:
					hero->name = (row[i]); break;
				case 2:
					hero->country = atoi(row[i]); break;
				case 3:
					hero->blood = atoi(row[i]); break;
				case 4:
					hero->introduction = (row[i]); break;
				case 5:
					hero->difficuty = atoi(row[i]); break;
				case 6:
					hero->attack = atoi(row[i]); break;
				case 7:
					hero->defense = atoi(row[i]); break;
				case 8:
					hero->burst = atoi(row[i]); break;
				case 9:
					hero->control = atoi(row[i]); break;
				case 10:
					hero->assistant = atoi(row[i]); break;
				case 11:
					hero->skill_1_id = atoi(row[i]); break;
				case 12:
					hero->skill_1_name = (row[i]); break;
				case 13:
					hero->skill_1_intro = (row[i]); break;
				case 14:
					hero->skill_2_id = atoi(row[i]); break;
				case 15:
					hero->skill_2_name = (row[i]); break;
				case 16:
					hero->skill_2_intro = (row[i]); break;
				case 17:
					hero->master_skill_id = atoi(row[i]); break;
				case 18:
					hero->master_skill_name = (row[i]); break;
				case 19:
					hero->master_skill_intro = (row[i]); break;
				default:
					break;
				}
			}
		}
		mysql_free_result(res);
	}
	else
	{
		nRet = -1;
	}
	return nRet;
}

void Hero::Get(Json::Value &hero)
{
    hero["idhero"] = idhero;
    hero["name"] = name;
    hero["country"] = country;
    hero["blood"] = blood;
    hero["introduction"] = introduction;
    hero["difficuty"] = difficuty;
    hero["attack"] = attack;
    hero["defense"] = defense;
    hero["burst"] = burst;
    hero["control"] = control;
    hero["assistant"] = assistant;
    hero["skill_1_id"] = skill_1_id;
    hero["skill_1_name"] = skill_1_name;
    hero["skill_1_intro"] = skill_1_intro;
    hero["skill_2_id"] = skill_2_id;
    hero["skill_2_name"] = skill_2_name;
    hero["skill_2_intro"] = skill_2_intro;
    hero["master_skill_id"] = master_skill_id;
    hero["master_skill_name"] = master_skill_name;
    hero["master_skill_intro"] = master_skill_intro;
}