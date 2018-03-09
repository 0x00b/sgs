#ifndef __FIGHTMAIN_SCENE_H__
#define __FIGHTMAIN_SCENE_H__

#include "model/include_all.h"
#include "SelectHero2Layer\SelectHero2Layer.h"
#include "./model/sgscard.h"
#include "Fight/FightEndLoseLayer.h"
#include "Fight/FightEndWinLayer.h"

USING_NS_CC;
using namespace ui;

class FightMain : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FightMain);

public:
	SelectHero2Layer *selectHero;	//选择武将层指针
private:
	Size win;
	TextField* txt_chat;	//聊天

	Label* chat[8];

	Sprite *chat_bg; //聊天背景
	Vector<SpriteFrame*> sha_vec;
	Vector<SpriteFrame*> shan_vec;
	Vector<SpriteFrame*> tao_vec;
	Sprite *animation_sha;
	Sprite *animation_shan;
	Sprite *animation_tao;
	ImageView* img_bg;	//背景图
	ImageView* img_hero[2];				//武将信息
	ImageView* img_hero_info_bg[2];	//用于在武将国家和姓名的背景色
	ImageView* img_hero_country[2];
	Label* lab_hero_name[2];
	ImageView* img_handcard_num_bg[2];	//手牌数背景
	Label* lab_handcard_num[2];	//手牌数
	ImageView* img_blood[2][4];	//血 最多四个 在初始化武将信息的时候初始化

	//ImageView* img_enemy_hero;				//对方武将信息
	//ImageView* img_enemy_hero_info_bg;	//用于在武将国家和姓名的背景色
	//ImageView* img_enemy_hero_country;
	//Label* lab_enemy_hero_name;
	//ImageView* img_enemy_handcard_num_bg;	//敌方手牌数背景
	//Label* lab_enemy_handcard_num;	//敌方手牌数

	ProgressTimer* pt_0;	//我方出手定时
	ProgressTimer* pt_1;	//敌方出手定时

	int stage;	//当前处于的阶段 出牌 弃牌 0：初始化 1：出牌 2：弃牌 3：对手回合 等待
	int status;				//当前可以点的牌数量
	Sprite* sp_handcard[20];	//手牌
	int i_current_card_num;	//当前手牌数
	ImageView* img_handcard_num[20];	//点数
	ImageView* img_handcard_flowercolor[20];	//花色
	int i_current_card[20];	//当前选中的手牌编号

	Button* btn_confirm;  //确定
	Button* btn_cancel;  //取消

	Label* lab_now_stage;	//显示当前阶段的标签
public:
	void InitHeroInfo();				//初始化敌我武将信息
	void Vec_create();
	bool onTouchHandCardBegan(Touch* touch, Event* event);		//手牌的触摸事件
	void onTouchHandCardMoved(Touch* touch, Event* event);
	bool onTouchHandCardEnded(Touch* touch, Event* event);
	void btn_confirm_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type);	//出牌确认事件
	void btn_cancel_card(Ref* sender, cocos2d::ui::Widget::TouchEventType type);	//出牌取消事件
	void UpdateHandCard();			//更新手牌
	void UpdateFightInfo(int i,int blood,int max_blood);			//更新 对战信息 血量 第一个参数0代表我 1代表对手 第二个参数代表血量 第三个参数最大血量
	void ShowMyBtnAndTimer();		//显示我的按钮和定时器
	void HideMyBtnAndTimer();		//隐藏我的按钮和定时器
	void ShowEnemyTimer();			//显示对手定时器
	void HideEnemyTimer();			//隐藏对手定时器

	void hid_sha(Node* sender);   //将杀的精灵隐藏
	void hid_shan(Node* sender);  //将闪的精灵隐藏
	void hid_tao(Node* sender);  //将桃的精灵隐藏
	void show_sha(int i);  //显示杀
	void show_shan(int i); //显示闪
	void show_tao(int i);  //显示桃
	void UpdateChat();  //更新聊天界面

	void setStatus(int i);
	int getStatus();
	void setStage(int i);

	void textFieldEvent(Ref * pSender, TextField::EventType type);  //textfield的回调函数
	void UpdateHandCardNum(int i,int cnt);		//更新手牌数 第一个参数0代表我 1代表对手 第二个参数代表手牌张数
	void UpdateStageLab(std::string stage_name);	//更新当前阶段
	void GameEnd(int i);		//游戏结束	0代表胜利 1代表失败
};

#endif // __FIGHTMAIN_SCENE_H__
