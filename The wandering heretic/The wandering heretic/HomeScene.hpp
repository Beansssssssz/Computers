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

  const int ARROWWIDTH = 56, ARROWHEIGHT = 36;
  const int MAX_SIZE = 80, MIN_SIZ = 20;
  bool _isIncrease;
  const int YDIFF = 100;//the in between the buttons
  const int XDIFF = 7;//the in between the Arrows to the button

  bool _mousePr;//the mouse priority
  bool _aboutOpen;
};
