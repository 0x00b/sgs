#include "game.h"



Game::Game() :m_nStatus(0)
{
	m_mPlayers.clear();
	m_mTables.clear();
}


Game::~Game()
{
}

int Game::StartUp()
{
	if (Listen())
	{
		Accept();
	}
	return 0;
}

int Game::UserRegist()
{
	return 0;
}

int Game::UserLogin()
{
	return 0;
}

int Game::UserQuit(Player * player)
{
	return 0;
}

int Game::MatchRoom(Player * player)
{
	return 0;
}

int Game::SelectGameMode()
{
	return 0;
}

int Game::GetGameMode()
{
	return 0;
}

int Game::CreateRoom()
{
	return 0;
}

int Game::EnterRoom(int roomId)
{
	return 0;
}

int Game::EnterRoomFast()
{
	return 0;
}

int Game::SearchRoom(int roomId)
{
	return 0;
}

int Game::Broadcast(std::string stMsg)
{
	return 0;
}

int Game::Listen()
{
	return 0;
}

int Game::Accept()
{
	return 0;
}
