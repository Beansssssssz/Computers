#include <SDL.h>

#include "PopUpWindow.hpp"

PopUpWindow::PopUpWindow(Button btnExit, SDL_Rect rect, RGBA color)
  :_btnExit(btnExit), _tab(rect), _color(color)
{
  _CorrectButton();
};

void PopUpWindow::Update(RenderWindow* window)
{
  window->CreateRect(&_tab, _color);
  Mouse* mouse = Mouse::GetMouse();
  //_btnExit.Update(mouse, MouseButtons::mbl)
};

//corrects the placement of the button in "tab" that opens
void PopUpWindow::_CorrectButton()
{
  int left = _tab.x + _tab.w;
  int top = _tab.y;
  int width = _btnExit.GetDstRect().w;
  int x = left - width;
  SDL_Rect dst= _btnExit.GetDstRect();
  dst.y = top;
  dst.x = x;
  _btnExit.SetSrcRect(dst);
};
