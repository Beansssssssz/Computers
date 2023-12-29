#pragma once

#include "Button.hpp"

#define BUTTON_ARR_SIZE 4

enum class HomeButtons {
  None = -1,
  Play,
  Settings,
  Help,
  Quit,
};

class HomeScene
{
public:
  HomeScene();
  ~HomeScene();

  int Update();
private:
  void UpdateButtons();
  void AboutWindowUpdate();

  void HandleInput();
  void ButtonResized();
  int CheckButtons();

  void CreateButtons();
  void CreateArrows();
  void CreateAboutWindow();

  HomeButtons _current;

  Button** _buttons;
  Square** _arrows;
  Square* _bg;

  Square* _aboutTex;
  Button* _aboutExit;

  bool* _keyPressed;

  const char ARROWWIDTH = 56, ARROWHEIGHT = 36;
  const char MAX_SIZE = 80, MIN_SIZ = 20;
  bool _isIncrease;

  const char MARGINY = 100;//the margin between the buttons
  const char MARGINX = 7;//the margin between the Arrows to the button
  const char MARGIN_EXIT = 8;// the margin between the x and the border

  bool _mousePr;//the mouse priority
  bool _aboutOpen; // if the about window is open(used for muiltple stuff)
};
