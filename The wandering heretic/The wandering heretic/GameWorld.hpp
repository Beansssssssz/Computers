#pragma once

#include "GamePlayer.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
#include "Button.hpp"
#include "Utils.hpp"

#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameWorld
{
public:
  GameWorld(json* data, std::string path);
  ~GameWorld();

  GameReturnValues Update();
private:
  void UpdateWorldOffset();
  void OffestAllVector(int offsetX, int offsetY, SDL_Rect* dst);
  void UpdateWorldEntities();
  GameReturnValues KeyboardUpdater();
  bool TouchedFinishLine();
  void PlayCompletedLevel();

  json* _data;
  std::string _path;

  GamePlayer* _player;
  std::vector<Entity*> _vec;
  std::vector<Enemy*> _enemyVec;;
  SDL_Rect _finishLine;
};

