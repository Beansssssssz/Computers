#include "Setting.hpp"

#include <iostream>
#include "RenderWindow.hpp"
#include "Audio.hpp"

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
/// updates the settings menu
/// </summary>
/// <param name="NeedExitGame">if true then displays the quit game button
/// otherwise does not</param>
/// <returns>1 or 0,1 means quit 0 means no action needed</returns>
int Settings::Update(bool NeedExitGame)
{
  if (!_tabOpen)
    return -1;

  Settings::PopUpWindow::Update();
  UpdateMusic();

  return 1;
};

/// <summary>
/// updates all the music elements in the class
/// </summary>
void Settings::UpdateMusic()
{
  Audio* audio = Audio::GetAudioInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  //updating the buttons
  _btnMusic->Update();
  _btnEffect->Update();

  //redering the buttons
  window->Render((Square*)_btnMusic);
  window->Render((Square*)_btnEffect);

  //checking to see if to change the music
  if (_btnMusic->GetIsPressed())
    _musicOn = !_musicOn;
  if (_btnEffect->GetIsPressed())
    _effectOn = !_effectOn;

  _slider->Update();
  int volume = _slider->GetValue();

  //audio->SetVolume(volume);
};

/// <summary>
/// Creates the buttons
/// </summary>
void Settings::CreateButtons(int marginx, int marginy) {
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/HomeButtons.png");

  SDL_Rect src{ 0, 0, 50, 50 }, dst{ 0, 0, 50, 50 };//{x, y, w, h)

  int ScreenW, ScreenH;
  window->GetWidthHeight(ScreenW, ScreenH);

  int x = ScreenW / 2 - 50 / 2,
  y = ScreenH / 2 - 50 / 2;
  dst.x = x; dst.y = y;

  _btnMusic = new Button(tex, src, dst);
  _btnEffect = new Button(tex, src, dst);
};

/// <summary>
/// Creates the Slider
/// </summary>
void Settings::CreateSlider() {
  SDL_Rect src{ 0, 0, 60, 60 }, dst{ 0, 0, 60, 60 };//{x, y, w, h)
  SDL_Color color{ 0,0,0,0 };

  _slider = new Slider(dst, 0, 0, color, 50);
};
