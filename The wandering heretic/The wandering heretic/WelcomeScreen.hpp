#pragma once

#include <SDL.h>

#include "Button.hpp"

class WelcomeScreen
{
public:
  WelcomeScreen();
  ~WelcomeScreen();

private:
  bool pressedKey;
  Button* btnPlay;
};
