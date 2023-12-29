#pragma once

#include "Button.hpp"
#include "Slider.hpp"
#include "PopUpWindow.hpp"
#include "WindowText.hpp"
#include "Audio.hpp"

// the margin between the text and the button
#define MARGIN 30;

class Settings : public PopUpWindow
{
public:
  Settings(Button* btnExit, SDL_Rect rect, SDL_Color color);
  ~Settings();

  int Update(bool NeedExitGame = false);

  static Settings* CreateSettings(int marginx = 350, int marginy = 150);
private:
  void UpdateMusic();
  void UpdateText();
  int UpdateQuitBtn();

  void CreateButtons(int marginx = 100, int marginy = 100);
  void CreateSlider(int marginx = 10, int w = 50, int h = 50);
  void CreateQuitButton();
  void CreateText();
  void CalculateMargin(int margin, int overall);

  Button* _btnMusic;//the on and off of the general music
  Button* _btnEffect;//the on and off for the effects

  bool _musicOn;//true if the music is on
  bool _effectOn;//true if the music is on
  Slider* _slider;//the slider of the music

  Button* _btnQuit;//exits to the home screen

  WindowText* _musicText;//the text depectiong the type of the button
  WindowText* _effectText;//the text depectiong the type of the button

  int _marginY;//teh margin between each btn/slider
};
