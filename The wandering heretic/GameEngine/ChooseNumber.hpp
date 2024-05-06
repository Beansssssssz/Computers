#pragma once

#include "Button.hpp"
#include "PopUpWindow.hpp"
#include "WindowText.hpp"

class ChooseNumber
{
public:
  ChooseNumber(char buttons_number);
  ~ChooseNumber();

  char Update(int unlocked = -1);
  bool GetIsOpen();
  void SetOpen(bool state);
private:
  bool UpdateWindow();
  char UpdateButtons(int unlocked);
  void WriteOnButtons(int unlocked);

  void CreateButtons();
  void CreateWindow();
  void CreateWindowText();

  Button** _btns; //the buttons array(dynamic depends on what number recived in the build function)
  char _len; //the amount of buttons

  Square* _lockedBtn; //the locked button texture to display out

  PopUpWindow* _tab; // the background of this
  WindowText* _text; //the text

  const char MAX_PER_ROW = 5;
};

