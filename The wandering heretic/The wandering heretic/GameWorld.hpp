#pragma once

#include "BasePlayer.hpp"
#include "Entity.hpp"
#include "Button.hpp"

#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameWorld
{
public:
  GameWorld(json* data, std::string path);
  ~GameWorld();

  bool Update();
private:
  void UpdateWorldPos();
  void OffestAllVector(int offsetX, int offsetY, SDL_Rect* dst);
  void UpdateWorldEntities();

  json* _data;
  std::string _path;

  BasePlayer* _player;
  Button* _settingsBtn;
  std::vector<Entity*> _vec;
};

