#pragma once

#include <SDL.h>

#include "Button.hpp"
#include "RenderWindow.hpp"

class PopUpWindow
{
public:
  PopUpWindow(Button btnExit, SDL_Rect tab, RGBA color);
  ~PopUpWindow();
  void Update(RenderWindow* window);
private:
  void _CorrectButton();

  Button _btnExit;
  SDL_Rect _tab;//the tab that the buttons are displayed on
  RGBA _color;
};
