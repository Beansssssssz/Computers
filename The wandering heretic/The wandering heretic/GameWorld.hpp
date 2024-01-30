#pragma once

#include "BasePlayer.hpp"
#include "Entity.hpp"
#include "Button.hpp"

#include <vector>

class GameWorld
{
public:
  GameWorld();
  ~GameWorld();

  bool Update();
private:
  BasePlayer* _player;
  Button* _settingsBtn;
  std::vector<Entity*> _vec;
};

