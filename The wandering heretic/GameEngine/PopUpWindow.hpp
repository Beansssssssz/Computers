#pragma once

#include <SDL.h>

#include "Button.hpp"

class PopUpWindow
{
public:
  PopUpWindow();
  ~PopUpWindow();

private:
  Button* btnExit;
};
