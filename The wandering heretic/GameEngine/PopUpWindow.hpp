#pragma once

#include "Button.hpp"
#include "RenderWindow.hpp"

class PopUpWindow
{
public:
  PopUpWindow(Button* btnExit, SDL_Rect tab, SDL_Color color, bool open = false);
  ~PopUpWindow();
  void Update();

  SDL_Rect GetRect();
  SDL_Color GetColor();

  void SetTab(bool val);
  bool GetTabOpen();
private:
  Button* _btnExit;
  SDL_Rect _tab;//the tab that the buttons are displayed on
  SDL_Color _color;

protected:
  void _CorrectButton();
  bool _tabOpen;
};
