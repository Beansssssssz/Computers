#pragma once

#include "BasePlayer.hpp"
#include "Server.hpp"

class GamePlayer : public BasePlayer
{
public:
  GamePlayer(std::vector<GIF*> gifs);
  ~GamePlayer();
  void Update(std::vector<Entity*> vec);

  UserData GetUserData();
  void SetUserData(UserData);
private:
  UserData _data;
};

