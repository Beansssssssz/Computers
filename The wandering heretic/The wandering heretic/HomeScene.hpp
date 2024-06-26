#pragma once

#include "Button.hpp"
#include "SignIn.hpp"
#include "SignUp.hpp"

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
  void UpdateLogins();
  void AboutWindowUpdate();

  void HandleInput();
  void ButtonResized();
  int CheckButtons();

  void CreateButtons();
  void CreateArrows();
  void CreateAboutWindow();
  void CreateLoginsWindows();

  HomeButtons _current;

  Button** _buttons;
  Square** _arrows;
  Square* _bg;

  Square* _aboutTex;
  Button* _aboutExit;

  SignIn* _signIn;
  SignUp* _signUp;
  Button* _logins;

  bool* _keyPressed;

  const char ARROWWIDTH = 56, ARROWHEIGHT = 36; //the orignial width and height
  const char MAX_SIZE = 80, MIN_SIZ = 20; //the max size and the min size of the arrows
  bool _isIncrease;

  const char MARGINY = 100;//the margin between the buttons
  const char MARGINX = 7;//the margin between the Arrows to the button
  const char MARGIN_EXIT = 8;// the margin between the x and the border

  bool _mousePr;//the mouse priority
  bool _aboutOpen; // if the about window is open(used for muiltple stuff)
};
