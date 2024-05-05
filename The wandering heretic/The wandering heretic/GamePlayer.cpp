#include "GamePlayer.hpp"

GamePlayer::GamePlayer(std::vector<GIF*> gifs)
  :BasePlayer(gifs), _data({})
{
  Server* server = Server::GetServerInstance();
  _data = server->GetLastUserData();
  if (_data.gameData == nullptr) {
    _data.gameData = new GameData{ 0,0,1 };
  }
}

GamePlayer::~GamePlayer()
{
  Server* server = Server::GetServerInstance();
  server->UpdateUserData(_data);

  BasePlayer::~BasePlayer();
}

/// <summary>
/// updates the player class
/// </summary>
/// <param name="vec"></param>
void GamePlayer:: Update(std::vector<Entity*> vec)
{
  BasePlayer::Update(vec);
}

UserData GamePlayer::GetUserData()
{
    return _data;
}

void GamePlayer::SetUserData(UserData data)
{
    _data = data;
}
