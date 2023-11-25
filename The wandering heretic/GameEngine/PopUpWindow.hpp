#pragma once

#include <SDL.h>

#include "Button.hpp"
#include "RenderWindow.hpp"

class PopUpWindow
{
public:
  PopUpWindow(Button btnExit, SDL_Rect tab, RGBA color, bool open = false);
  //~PopUpWindow();
  void Update(RenderWindow* window);
  void OpenTab();
  void CloseTab();
private:
  void _CorrectButton();

  Button _btnExit;
  SDL_Rect _tab;//the tab that the buttons are displayed on
  RGBA _color;

  bool _tabOpen;
};
