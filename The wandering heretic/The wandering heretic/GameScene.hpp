#pragma once

#include "LevelEditor.hpp"
#include "GameWorld.hpp"

#include "Button.hpp"
#include "WindowText.hpp"
#include "ChooseNumber.hpp"

#include <string>

class GameScene
{
public:
  GameScene();
  ~GameScene();

  GameReturnValues Update();
private:

  Square* _bg;
  LevelEditor* _edit;
  GameWorld* _world;
  ChooseNumber* _cn;
};
