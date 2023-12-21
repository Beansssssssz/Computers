#include <SDL.h>
#include <iostream>

#include "PopUpWindow.hpp"
#include "Square.hpp"

PopUpWindow::PopUpWindow(Button btnExit, SDL_Rect rect, SDL_Color color, bool open)
  :_btnExit(NULL), _tab(rect), _color(color), _tabOpen(open)
{
  _btnExit = new Button(btnExit);
  _CorrectButton();
};

PopUpWindow::~PopUpWindow()
{

};

void PopUpWindow::Update()
{
  if (!_tabOpen)
    return;

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  
  Mouse* mouse = Mouse::GetMouseInstance();

  window->DisplayRect(&_tab, _color);
  window->Render((Square*)_btnExit);

  _btnExit->Update();
  if (_btnExit->GetIsPressed())
    CloseTab();
};

void PopUpWindow::OpenTab()
{
  _tabOpen = true;
};

void PopUpWindow::CloseTab()
{
  _tabOpen = false;
};

//corrects the placement of the button in "tab" that opens
void PopUpWindow::_CorrectButton()
{
  int right = _tab.x + _tab.w;
  int top = _tab.y;

  SDL_Rect* dst = _btnExit->GetDstRect();

  dst->y = top;
  dst->x = right - dst->w;
};
