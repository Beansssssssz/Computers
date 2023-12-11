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
  void DisplayText();
  //void ChangeCurrent(int increment);

  HomeButton _current;

  Button** _buttons;
  Square* _bg;

  bool* _keyPressed;
};
