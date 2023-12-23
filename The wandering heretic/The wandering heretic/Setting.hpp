#pragma once

#include "Button.hpp"
#include "Slider.hpp"
#include "PopUpWindow.hpp"

class Settings : public PopUpWindow
{
public:
  Settings(Button* btnExit, SDL_Rect rect, SDL_Color color);
  ~Settings();

  int Update(bool NeedExitGame = false);
  void UpdateMusic();

  void CreateButtons(int marginx = 100, int marginy = 100);
  void CreateSlider();
private:
  Button* _btnMusic;//the on and off of the general music
  Button* _btnEffect;//the on and off for the effects

  bool _musicOn;//true if the music is on
  bool _effectOn;//true if the music is on
  Slider* _slider;//the slider of the music

  Button* _quit;//exits to the home screen
};
