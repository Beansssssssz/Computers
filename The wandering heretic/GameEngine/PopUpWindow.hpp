#pragma once

#include "Button.hpp"
#include "RenderWindow.hpp"

class PopUpWindow
{
public:
  PopUpWindow(Button btnExit, SDL_Rect tab, SDL_Color color, bool open = false);
  ~PopUpWindow();
  void Update();
  void OpenTab();
  void CloseTab();
private:
  void _CorrectButton();

  Button* _btnExit;
  SDL_Rect _tab;//the tab that the buttons are displayed on
  SDL_Color _color;

  bool _tabOpen;
};
