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
  void PlayerFell();
  void PlayerWasHit();
  GameReturnValues DisplayDeadWindow();

  json* _data;
  std::string _path;

  GamePlayer* _player;
  std::vector<Entity*> _vec;
  std::vector<Enemy*> _enemyVec;
  Square* _finishLine;

  Uint32 _startTime;
  int _highestYBlock;
  Uint32 _showDeadWindow;

  static constexpr SDL_Color GAME_OVER_RECT_COLOR{ 0,0,0, 200 }; //the game over overlay rect color
  static constexpr SDL_Color GAME_OVER_TEXT_COLOR{ 255,0,0, 255 }; //the game over text color
  static constexpr uint16_t GAME_OVER_TEXT_SIZE = 50; //the game over text size
  static constexpr uint16_t GAME_OVER_TIMER = 500; //how long to display the game over message
};

