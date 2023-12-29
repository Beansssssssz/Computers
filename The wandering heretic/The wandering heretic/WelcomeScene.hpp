#pragma once
#include <SDL.h>

#include "Button.hpp"
#include "Keyboard.hpp"
#include "WindowText.hpp"

class WelcomeScene {
public:
  WelcomeScene();
  ~WelcomeScene();
  bool Update();
  void SetKeyPressed(bool keyPressed);

private:
  Square* _bg;
  WindowText* _winText;
  bool _keyPressed;
};
