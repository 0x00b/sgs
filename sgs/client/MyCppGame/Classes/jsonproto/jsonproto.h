#ifndef _SGS_JSON_PROTO_H_
#define _SGS_JSON_PROTO_H_

enum EJPROTO
{
	E_PROTO_NM_LEN = 20,

	E_Player = 0,
	E_ReqLogin,
	E_ReqLoginUc,
	E_ReqLogout,
	E_ReqLogoutUc,
	E_ReqRegist,
	E_ReqRegistUc,
	E_ReqUpdatePwd,
	E_ReqUpdatePwdUc,
	E_ReqGetFriends,
	E_ReqGetFriendsUc,
	E_ReqAddFriends,
	E_ReqAddFriendsUc,
	E_ReqDeleteFriend,
	E_ReqDeleteFriendUc,
	E_Room,
	E_ReqCreateRoom,
	E_ReqCreateRoomUc,
	E_ReqSearchRoom,
	E_ReqSearchRoomUc,
	E_ReqEnterRoom,
	E_ReqEnterRoomFast,
	E_ReqEnterRoomBc,
	E_ReqQuitRoom,
	E_ReqQuitRoomBc,
	E_ReqReady,
	E_ReqReadyBc,
	E_ReqEmotionBC,

	E_PROTO_END,
};

const char SJPROTO[E_PROTO_END][E_PROTO_NM_LEN] =
	{
		{"player"},
		{"ReqLogin"},
		{"ReqLoginUc"},
		{"ReqLogout"},
		{"ReqLogoutUc"},
		{"ReqRegist"},
		{"ReqRegistUc"},
		{"ReqUpdatePwd"},
		{"ReqUpdatePwdUc"},
		{"ReqGetFriends"},
		{"ReqGetFriendsUc"},
		{"ReqAddFriends"},
		{"ReqAddFriendsUc"},
		{"ReqDeleteFriend"},
		{"ReqDeleteFriendUc"},
		{"Room"},
		{"ReqCreateRoom"},
		{"ReqCreateRoomUc"},
		{"ReqSearchRoom"},
		{"ReqSearchRoomUc"},
		{"ReqEnterRoom"},
		{"ReqEnterRoomFast"},
		{"ReqEnterRoomBc"},
		{"ReqQuitRoom"},
		{"ReqQuitRoomBc"},
		{"ReqReady"},
		{"ReqReadyBc"},
		{"ReqEmotionBC"},
};
//玩家信息
enum EPlayer
{
	EPlayer_id = 0,
	EPlayer_account,
	EPlayer_passwd,
	EPlayer_name,
	EPlayer_avatar,
	EPlayer_sex,
	EPlayer_exp,
	EPlayer_level,
	EPlayer_status,
	EPlayer_gamestatus,
	EPlayer_seatid,
	EPlayer_registdate,
	EPlayer_remark,
};

const char SPlayer[][E_PROTO_NM_LEN] =
	{
		{"id"},
		{"account"},
		{"passwd"},
		{"name"},
		{"avatar"},
		{"sex"},
		{"exp"},
		{"level"},
		{"status"},
		{"gamestatus"},
		{"seatid"},
		{"registdate"},
		{"remark"},
};
enum ERoom
{
	ERoom_room_id = 0,
	ERoom_name,			//room's name
	ERoom_type,				//room type
	ERoom_max_player_cnt ,		//max player cnt
	ERoom_player_cnt ,			//current player cnt
	ERoom_match_seat_way,			//random or by order to give seat number
	ERoom_status,				//room's status
	ERoom_player_master,				//room master
	ERoom_player_r ,	//players in the room
};
const char SRoom[][E_PROTO_NM_LEN] =
{
	{"room_id"},
	{"name"},			//room's name
	{"type"},				//room type
	{"max_player_cnt"},		//max player cnt
	{"player_cnt"},			//current player cnt
	{"match_seat_way"},			//random or by order to give seat number
	{"status"},				//room's status
};


/*

syntax = "proto3";

package proto.game;

//玩家信息
message Player
{
	int32 id = 1; 		
	string account = 2;
	string passwd = 3;		
	string name = 4;	
	string avatar = 5;
	int32 sex = 6;
	int32 exp = 7;
	int32 level = 8;	
	int32 status = 9;
	int32 gamestatus = 10;
	int32 seatid = 11;
	string registdate = 12;
	string remark = 13;
}

//客户端上行结构体
//请求登陆
message ReqLogin
{
	string account	= 1;
	string pwd	= 2;
}

//服务端下发结构体
//登录成功返回（单播）
message ReqLoginUc
{	
	int32 code = 1;	//返回码，0成功 1失败
	Player player = 2;
}

//请求退出游戏
message ReqLogout
{
	Player player = 1;
}
//玩家退出请求返回
message ReqLogoutUc
{
	int32 code = 1;
	string remark = 2;
}

message ReqRegist
{
	Player player = 1;
}
message ReqRegistUc
{
	int32 code = 1;
	Player player = 2;
}
message ReqUpdatePwd
{
	string account = 1;
	string oldpasswd = 2;
	string newpasswd = 3;
}
message ReqUpdatePwdUc
{
	int32 code = 1;
}
message ReqGetFriends
{
}
message ReqGetFriendsUc
{
	int32 code = 1;
	repeated Player frieds = 2;
}
message ReqAddFriends
{
	Player friend = 1;
}
message ReqAddFriendsUc
{
	int32 code = 1;
	Player friend = 2;
}
message ReqDeleteFriend
{
	Player friend = 1;
}
message ReqDeleteFriendUc
{
	int32 code = 2;
}

message Room
{
	int32 room_id = 1;
	string	name = 2;				//room's name
	int32 type = 3;					//room type
	int32 max_player_cnt = 4;			//max player cnt
	int32 player_cnt = 5;				//current player cnt
	int32 match_seat_way = 6;			//random or by order to give seat number
	int32 status = 7;					//room's status
	repeated Player players = 8;	//players in the room
	Player master = 9;				//room master
}

message ReqCreateRoom
{
	Room room = 1;
}
message ReqCreateRoomUc
{
	int32 code = 1;
	Room room = 2;
}
message ReqSearchRoom
{
	int32 roomid = 1;
}
message ReqSearchRoomUc
{
	int32 code = 1;
	Room room = 2;
}

message ReqEnterRoom
{
	int32 roomid = 1;
}

message ReqEnterRoomFast
{

}

message ReqEnterRoomBc
{
	int32 code = 1;
	Player player = 2;
	Room room = 3;
}
message ReqQuitRoom
{
	int32 roomid = 1;
}
message ReqQuitRoomBc
{
	int32 code = 1;
	Player player = 2;
}

message ReqReady
{
	int32 roomid = 1;
}
message ReqReadyBc
{
	int32 code = 1;
	Player player = 2;
}


//广播互动表情
message ReqEmotionBC
{
    int32 seatid = 1;
	int32 type = 2;
}

*/
#endif