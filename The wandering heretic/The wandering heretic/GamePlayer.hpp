#pragma once

#include "BasePlayer.hpp"

class GamePlayer : public BasePlayer
{
public:
  GamePlayer(std::vector<GIF*> gifs);
  void Update(std::vector<Entity*> vec);

private:
};

