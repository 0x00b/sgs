-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: sgs_db
-- ------------------------------------------------------
-- Server version	5.7.20-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `friends`
--

DROP TABLE IF EXISTS `friends`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `friends` (
  `idplayer` int(11) NOT NULL,
  `idfriend` int(11) NOT NULL,
  `type` int(11) DEFAULT NULL,
  `remark` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idplayer`,`idfriend`),
  KEY `FK_FRIENDS_ID_PLAYER_idx` (`idfriend`),
  CONSTRAINT `FK_FRIENDS_ID_FRIEND` FOREIGN KEY (`idplayer`) REFERENCES `player` (`idplayer`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_FRIENDS_ID_PLAYER` FOREIGN KEY (`idfriend`) REFERENCES `player` (`idplayer`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `friends`
--

LOCK TABLES `friends` WRITE;
/*!40000 ALTER TABLE `friends` DISABLE KEYS */;
/*!40000 ALTER TABLE `friends` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hero`
--

DROP TABLE IF EXISTS `hero`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hero` (
  `idhero` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `country` int(11) DEFAULT NULL,
  `blood` int(11) DEFAULT NULL,
  `introduction` varchar(512) DEFAULT NULL,
  `difficuty` int(11) DEFAULT '0',
  `attack` int(11) DEFAULT '0',
  `defense` int(11) DEFAULT '0',
  `burst` int(11) DEFAULT '0',
  `control` int(11) DEFAULT '0',
  `assistant` int(11) DEFAULT '0',
  `skill_1_id` int(11) DEFAULT NULL,
  `skill_1_name` varchar(45) DEFAULT NULL,
  `skill_1_intro` varchar(512) DEFAULT NULL,
  `skill_2_id` int(11) DEFAULT NULL,
  `skill_2_name` varchar(45) DEFAULT NULL,
  `skill_2_intro` varchar(512) DEFAULT NULL,
  `master_skill_id` int(11) DEFAULT NULL,
  `master_skill_name` varchar(45) DEFAULT NULL,
  `master_skill_intro` varchar(512) DEFAULT NULL,
  `remark` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idhero`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hero`
--

LOCK TABLES `hero` WRITE;
/*!40000 ALTER TABLE `hero` DISABLE KEYS */;
INSERT INTO `hero` VALUES (1,'刘备',2,4,'先主姓刘，讳备，字玄德，涿郡涿县人，汉景帝子中山靖王胜之后也。以仁德治天下。',2,1,2,0,0,3,1,'仁德',' 出牌阶段，你可以将任意张手牌交给其他角色，然后你于此阶段内给出第二张手牌时，你回复1点体力。',0,'',NULL,2,'激将',' 主公技，其他蜀势力角色可以在你需要时代替你使用或打出【杀】。',NULL),(2,'孙权',3,4,'吴大帝，字仲谋，吴郡富春县人。统领吴与蜀魏三足鼎立，制衡天下。',2,1,2,3,1,0,3,'制衡','出牌阶段限一次，你可以弃置任意张牌，然后摸等量的牌。',0,NULL,NULL,4,'救援','主公技，锁定技，其他吴势力角色对你使用【桃】回复的体力+1。',NULL),(3,'曹操',1,4,'魏武帝曹操，字孟德，小名阿瞒、吉利，沛国谯人。精兵法，善诗歌，乃治世之能臣，乱世之奸雄也。',1,0,3,1,0,0,5,'奸雄',' 当你受到伤害后，你可以获得造成此伤害的牌。',0,NULL,NULL,6,'护驾','主公技，其他魏势力角色可以在你需要时代替你使用或打出【闪】。',NULL),(4,'关羽',2,4,'字云长，本字长生，并州河东解州人。五虎上将之首，爵至汉寿亭侯，谥曰“壮缪侯”。被奉为“关圣帝君”，崇为“武圣”。',1,2,1,0,0,0,7,'武圣',' 你可以将一张红色牌当【杀】使用或打出。',0,NULL,NULL,0,NULL,NULL,NULL),(5,'张飞',2,4,'字翼德，涿郡人，燕颔虎须，豹头环眼。有诗云：“长坂坡头杀气生，横枪立马眼圆睁。一声好似轰雷震，独退曹家百万兵”。',1,3,0,1,0,0,8,'咆哮','锁定技，你使用【杀】无次数限制。',NULL,NULL,NULL,NULL,NULL,NULL,NULL),(6,'吕布',4,4,'字奉先，五原郡九原县人。三国第一猛将，曾独力战刘关张三人，其武力世之无双。时人语曰：“人中有吕布，马中有赤兔。”',1,2,1,0,0,1,9,'无双','锁定技，你使用的【杀】需两张【闪】才能抵消；与你进行【决斗】的角色每次需打出两张【杀】。',NULL,NULL,NULL,NULL,NULL,NULL,NULL),(7,'赵云',2,4,'字子龙，常山真定人。身长八尺，姿颜雄伟。长坂坡单骑救阿斗，先主云：“子龙一身都是胆也。”',1,2,1,0,0,0,10,'龙胆','你可以将一张【杀】当【闪】、【闪】当【杀】使用或打出。',NULL,NULL,NULL,NULL,NULL,NULL,NULL),(8,'吕蒙',3,4,'字子明，汝南富陂人。陈寿评曰：“吕蒙勇而有谋断，识军计，谲郝普，擒关羽，最其妙者。初虽轻果妄杀，终于克己，有国士之量，岂徒武将而已乎！”',1,1,2,1,0,0,11,'克己','若你没有在出牌阶段内使用或打出过【杀】，则你可以跳过弃牌阶段。',NULL,NULL,NULL,NULL,NULL,NULL,NULL),(9,'许褚',1,4,'字仲康，谯国谯县人。和典韦一同统率着曹操的亲卫队“虎卫军”。因为他十分勇猛，所以有“虎痴”的绰号。曾有裸衣斗马超之举。',1,3,0,0,0,0,12,'裸衣','摸牌阶段，你可以少摸一张牌，然后本回合你使用【杀】或【决斗】造成的伤害+1。',NULL,NULL,NULL,NULL,NULL,NULL,NULL),(10,'马超',2,4,'字孟起，扶风茂陵人。面如冠玉，目如流星，虎体猿臂，彪腹狼腰，声雄力猛。因衣着讲究，举止非凡，故人称“锦马超”。麾铁骑，捻金枪。',1,2,0,0,1,0,13,'马术','锁定技，你计算与其他角色的距离-1。',14,'铁骑','当你使用【杀】指定目标后，你可以进行判定，若结果为红色，该角色不能使用【闪】。',NULL,NULL,NULL,NULL),(11,'甄姬',1,3,'中山无极人，别称甄洛或甄宓，庙号文昭甄皇后。魏文帝曹丕的正室。懂诗文，有倾国倾城之貌，《洛神赋》即是曹植为她所作。',1,0,2,4,0,0,15,'倾国','你可以将一张黑色手牌当【闪】使用或打出。',16,'洛神','准备阶段，你可以进行判定，若结果为黑色，你获得此牌，然后你可以重复此流程。',NULL,NULL,NULL,NULL),(12,'大乔',3,3,'庐江皖县人，为乔公长女，孙策之妻，小乔之姊。与小乔并称为“江东二乔”，容貌国色流离。',2,0,2,0,2,1,17,'国色','你可以将一张方块牌当【乐不思蜀】使用。',18,'流离','当你成为【杀】的目标时，你可以弃置一张牌并将此【杀】转移给你攻击范围内的一名其他角色。',NULL,NULL,NULL,NULL),(13,'黄月英',2,3,'荆州沔南白水人，沔阳名士黄承彦之女，诸葛亮之妻，诸葛瞻之母。容貌甚丑，而有奇才：上通天文，下察地理，韬略近于诸书无所不晓，诸葛亮在南阳闻其贤而迎娶。',1,1,0,5,0,0,19,'集智',' 当你使用普通锦囊牌时，你可以摸一张牌。',20,'英才','锁定技，你使用锦囊牌无距离限制。',NULL,NULL,NULL,NULL),(14,'貂蝉',4,3,'中国古代四大美女之一，有闭月羞花之貌。司徒王允之义女，由王允授意施行连环计，离间董卓、吕布，借布手除卓。后貂蝉成为吕布的妾。',2,3,1,1,0,0,21,'离间','出牌阶段限一次，你可以弃置一张牌，令一名男性角色视为对另一名男性角色使用一张【决斗】。',22,'闭月','结束阶段，你可以摸一张牌。',NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `hero` ENABLE KEYS */;
INSERT INTO `hero` VALUES (1,'刘备',2,4,'先主姓刘，讳备，字玄德，涿郡涿县人，汉景帝子中山靖王胜之后也。以仁德治天下。',
2,1,2,0,0,3,1,'仁德',' 出牌阶段，你可以将任意张手牌交给其他角色，然后你于此阶段内给出第二张手牌时，你回复1点体力。',0,'',NULL,2,
'激将',' 主公技，其他蜀势力角色可以在你需要时代替你使用或打出【杀】。',NULL)

INSERT INTO `hero` VALUES (15,'周瑜',3,3,'字公瑾，庐江舒县人，任东吴三军大都督，雄姿英发，人称“美周郎”。赤壁之战前，巧用反间计杀了精通水战的叛将蔡瑁、张允。',
2,1,2,0,0,3,23,'英姿','摸牌阶段，你可以多摸一张牌。',24,'反间','出牌阶段限一次，你可以令一名其他角色选择一种花色，然后该角色获得你的一张手牌并展示之，若此牌的花色与其所选的花色不同，则你对其造成1点伤害。',0,
NULL,NULL,NULL)

INSERT INTO `hero` VALUES (16,'郭嘉',1,3,'字奉孝，颍川阳翟人，官至军师祭酒。惜天妒英才，英年早逝。有诗云：“良计环环不遗策，每临制变满座惊”。',
2,0,2,2,0,3,25,'天妒',' 当你的判定牌生效后，你可以获得此牌。',26,'遗计 ','当你受到1点伤害后，你可以观看牌堆顶的两张牌，然后将这些牌交给任意角色。',0,
NULL,NULL,NULL)

UNLOCK TABLES;

--
-- Table structure for table `player`
--

DROP TABLE IF EXISTS `player`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player` (
  `idplayer` int(11) NOT NULL AUTO_INCREMENT,
  `account` varchar(45) NOT NULL,
  `passwd` varchar(45) NOT NULL,
  `sex` int(11) DEFAULT NULL,
  `avatar` varchar(255) DEFAULT NULL,
  `level` int(11) DEFAULT NULL,
  `exp` int(11) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `regist_date` varchar(10) DEFAULT NULL,
  `remark` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idplayer`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='player infomation';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player`
--

LOCK TABLES `player` WRITE;
/*!40000 ALTER TABLE `player` DISABLE KEYS */;
INSERT INTO `player` VALUES (1,'admin','YWRtaW4=',0,NULL,100,0,1,'2018-01-16','admin');
/*!40000 ALTER TABLE `player` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_hero`
--

DROP TABLE IF EXISTS `player_hero`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_hero` (
  `idplayer_hero` int(11) NOT NULL AUTO_INCREMENT,
  `idplayer` int(11) DEFAULT NULL,
  `idhero` int(11) DEFAULT NULL,
  `level` int(11) DEFAULT NULL,
  `exp` int(11) DEFAULT NULL,
  `remark` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idplayer_hero`),
  KEY `PLAYER_HERO_ID_idx` (`idhero`),
  KEY `FK_PH_PLAYER_ID_idx` (`idplayer`),
  CONSTRAINT `FK_PH_HERO_ID` FOREIGN KEY (`idhero`) REFERENCES `hero` (`idhero`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_PH_PLAYER_ID` FOREIGN KEY (`idplayer`) REFERENCES `player` (`idplayer`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_hero`
--

LOCK TABLES `player_hero` WRITE;
/*!40000 ALTER TABLE `player_hero` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_hero` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-01-19 16:44:41
