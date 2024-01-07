#include <SDL.h>
#include <iostream>

#include "PopUpWindow.hpp"
#include "Square.hpp"


PopUpWindow::PopUpWindow(Button* btnExit, SDL_Rect rect, SDL_Color color, bool open)
  :_btnExit(btnExit), _tab(rect), _color(color), _tabOpen(open)
{
  _CorrectButton();
};

PopUpWindow::~PopUpWindow()
{
  delete _btnExit;
};

void PopUpWindow::Update()
{
  if (!_tabOpen)
    return;

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Mouse* mouse = Mouse::GetMouseInstance();

  window->DisplayRect(&_tab, _color);

  if (_btnExit == NULL)
    return;

  window->Render((Square*)_btnExit);
  _btnExit->Update();
  if (_btnExit->GetIsPressed())
    SetTab(false);
};

/// <summary>
/// rerturns the rect of the tab
/// </summary>
/// <returns></returns>
SDL_Rect PopUpWindow::GetRect() {
  return _tab;
}

/// <summary>
/// returns the color of the tab
/// </summary>
/// <returns></returns>
SDL_Color PopUpWindow::GetColor() {
  return _color;
}

/// <summary>
/// Sets the tab open in val is true, otherwise closes the tabs
/// </summary>
void PopUpWindow::SetTab(bool val)
{
  _tabOpen = val;
};

/// <summary>
/// Returns the if the tab is open or not
/// </summary>
bool PopUpWindow::GetTab()
{
  return _tabOpen;
};


/// <summary>
/// corrects the placement of the button in "tab" that opens
/// </summary>
void PopUpWindow::_CorrectButton()
{
  if (_btnExit == NULL)
    return;

  int right = _tab.x + _tab.w;
  int top = _tab.y;

  SDL_Rect* dst = _btnExit->GetDstRect();

  dst->y = top;
  dst->x = right - dst->w;
};
