#pragma once

#include "Button.hpp"

class HomeScene
{
public:
  HomeScene();
  ~HomeScene();

  void Update();
private:
  Button* _btnExit;
  Button* _btnStart;
  Button* _btnSettings;
  Square* _bg;
};
