#include <SDL.h>
#include <iostream>

#include "PopUpWindow.hpp"
#include "Square.hpp"

PopUpWindow::PopUpWindow(Button btnExit, SDL_Rect rect, RGBA color, bool open)
  :_btnExit(btnExit), _tab(rect), _color(color), _tabOpen(open)
{
  _CorrectButton();
};

void PopUpWindow::Update(RenderWindow* window)
{
  if (!_tabOpen)
    return;
  
  Mouse* mouse = Mouse::GetMouse();

  window->CreateRect(&_tab, _color);
  window->Render(Square(_btnExit));

  _btnExit.Update();
  if (_btnExit.GetIsPressed())
    CloseTab();
};

void PopUpWindow::OpenTab()
{
  _tabOpen = true;
};

void PopUpWindow::CloseTab()
{
  std::cout << "sdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
  _tabOpen = false;
};

//corrects the placement of the button in "tab" that opens
void PopUpWindow::_CorrectButton()
{
  int right = _tab.x + _tab.w;
  int top = _tab.y;

  SDL_Rect* dst = _btnExit.GetDstRect();

  dst->y = top;
  dst->x = right - dst->w;
};
