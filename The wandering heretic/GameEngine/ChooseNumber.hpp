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

  Button** _btns;
  char _len;

  Square* _lockedBtn;

  PopUpWindow* _tab;
  WindowText* _text;

  const char MAX_PER_ROW = 5;
};

