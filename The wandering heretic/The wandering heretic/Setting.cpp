#include "Setting.hpp"

#include <iostream>
#include "RenderWindow.hpp"

Settings::Settings()
  :_btnEffect(NULL), _btnMusic(NULL), _slider(NULL),
  _musicOn(true), _effectOn(true), _close(NULL), _quit(NULL)
{
  CreateButtons();
  CreateSlider();
  CreateSettingsBackground();
};

Settings::~Settings()
{
  delete _btnMusic, _btnEffect,
    _slider, _close, _exit;
}

/// <summary>
/// TODO
/// </summary>
/// <param name="NeedExitGame"></param>
/// <returns></returns>
int Settings::Update(bool NeedExitGame)
{
  RenderSettingsBackground();
  return 1;
};

void Settings::RenderSettingsBackground() {
  Mouse* mouse = Mouse::GetMouseInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();


  window->DisplayRect(&_bg, BGCOLOR);
};

/// <summary>
/// Creates the buttons
/// </summary>
void Settings::CreateButtons() {
  SDL_Rect src{ 0, 0, WIDTH, HEIGHT }, dst{ 0, 0, WIDTH, HEIGHT };//{x, y, w, h)

  int ScreenW, ScreenH;
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->GetWidthHeight(ScreenW, ScreenH);

  int x = ScreenW / 2 - WIDTH / 2,
  y = ScreenH / 2 - HEIGHT / 2;
  dst.x = x; dst.y = y;

  _btnMusic = new Button(NULL, src, dst);
  _btnEffect = new Button(NULL, src, dst);
};

/// <summary>
/// Creates the Slider
/// </summary>
void Settings::CreateSlider() {
  SDL_Rect src{ 0, 0, WIDTH, HEIGHT }, dst{ 0, 0, WIDTH, HEIGHT };//{x, y, w, h)
  SDL_Color color{ 0,0,0,0 };

  _slider = new Slider(dst, 0, 0, color, 50);
};

/// <summary>
/// Creates the Settings Backround
/// </summary>
void Settings::CreateSettingsBackground() {
  int ScreenW, ScreenH;
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->GetWidthHeight(ScreenW, ScreenH);

  int x = ScreenW / 2 - WIDTH / 2,
    y = ScreenH / 2 - HEIGHT / 2;
  SDL_Rect temp{x, y, WIDTH, HEIGHT};
  _bg = temp;
};
