#pragma once

#include "Button.hpp"
#include "PopUpWindow.hpp"
#include "WindowText.hpp"

class ChooseNumber
{
public:
  ChooseNumber(char buttons_number);
  ~ChooseNumber();

  char Update();
  bool GetIsOpen();
  void SetOpen(bool state);
private:
  bool UpdateWindow();
  char UpdateButtons();
  void WriteOnButtons();

  void CreateButtons();
  void CreateWindow();
  void CreateWindowText();

  Button** _btns;
  char _len;

  PopUpWindow* _tab;
  WindowText* _text;

  const char MAX_PER_ROW = 5;
};

