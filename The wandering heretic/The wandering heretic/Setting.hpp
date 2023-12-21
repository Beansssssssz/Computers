#pragma once

#include "Button.hpp"
#include "Slider.hpp"
#include "PopUpWindow.hpp"

class Settings
{
public:
  Settings();
  ~Settings();

  int Update(bool NeedExitGame = false);

  void RenderSettingsBackground();

  void CreateButtons();
  void CreateSlider();
  void CreateSettingsBackground();
private:
  Button* _btnMusic;//the on and off of the general music
  Button* _btnEffect;//the on and off for the effects

  bool _musicOn;//true if the music is on
  bool _effectOn;//true if the music is on
  Slider* _slider;//the slider of the music

  Button* _quit;//exits to the home screen
  Button* _close;//closes the screen

  SDL_Rect _bg;
  const SDL_Color BGCOLOR{100, 100, 100, 255};
  const int WIDTH = 600;
  const int HEIGHT = 600;
};
