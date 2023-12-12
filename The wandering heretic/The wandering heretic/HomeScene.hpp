#pragma once

#include "Button.hpp"
#define BUTTON_ARR_SIZE 4

enum class HomeButton {
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

  void Update();
private:
  void HandleInput();
  void CreateButtons();
  void CreateArrows();
  void InputToButtons();
  void ButtonResized();
  //void ChangeCurrent(int increment);

  HomeButton _current;

  Button** _buttons;
  Square** _arrows;
  Square* _bg;

  bool* _keyPressed;

  const int ARROWWIDTH = 56, ARROWHEIGHT = 36;
  const int MAX_SIZE = 80, MIN_SIZ = 20;
  bool _isIncrease;
  const int YDIFF = 100;//the in between the buttons
  const int XDIFF = 7;//the in between the Arrows to the button
};
