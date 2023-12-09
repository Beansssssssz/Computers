#pragma once

#include "Button.hpp"

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
  //void CreateButton();
  void DisplayText();
  void ChangeCurrent(int increment);

  HomeButton _current;

  Button* _btnQuit;
  Button* _btnPlay;
  Button* _btnSettings;
  Button* _btnHelp;
  Square* _bg;

  bool* _keyPressed;
};
