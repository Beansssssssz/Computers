#pragma once

#include "Square.hpp"

enum class Mode
{

};

class GameScene
{
public:
  GameScene();
  ~GameScene();

  int Update();
private:

  Square* _bg;
};
