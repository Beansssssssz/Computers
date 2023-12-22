#include "Setting.hpp"

#include <iostream>
#include "RenderWindow.hpp"

Settings::Settings(Button* btnExit, SDL_Rect rect, SDL_Color color)
  :Settings::PopUpWindow(btnExit, rect, color),
  _btnEffect(NULL), _btnMusic(NULL), _slider(NULL),
  _musicOn(true), _effectOn(true), _quit(NULL)
{
  CreateButtons();
  CreateSlider();
};

Settings::~Settings()
{
  delete _btnMusic, _btnEffect,
  _slider, _quit;
}

/// <summary>
/// TODO
/// </summary>
/// <param name="NeedExitGame"></param>
/// <returns></returns>
int Settings::Update(bool NeedExitGame)
{
  if (!_tabOpen)
    return -1;

  Settings::PopUpWindow::Update();


  return 1;
};

/// <summary>
/// Creates the buttons
/// </summary>
void Settings::CreateButtons() {
  SDL_Rect src{ 0, 0, 50, 50 }, dst{ 0, 0, 50, 50 };//{x, y, w, h)

  int ScreenW, ScreenH;
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->GetWidthHeight(ScreenW, ScreenH);

  int x = ScreenW / 2 - 50 / 2,
  y = ScreenH / 2 - 50 / 2;
  dst.x = x; dst.y = y;

  _btnMusic = new Button(NULL, src, dst);
  _btnEffect = new Button(NULL, src, dst);
};

/// <summary>
/// Creates the Slider
/// </summary>
void Settings::CreateSlider() {
  //SDL_Rect src{ 0, 0, WIDTH, HEIGHT }, dst{ 0, 0, WIDTH, HEIGHT };//{x, y, w, h)
  //SDL_Color color{ 0,0,0,0 };

  //_slider = new Slider(dst, 0, 0, color, 50);
};
