#pragma once

#include "PopUpWindow.hpp"
#include "WindowText.hpp"

class PopUpMessageBox : public PopUpWindow
{
public:
  PopUpMessageBox(Button* btnExit, SDL_Rect tab, SDL_Color color, std::string text,bool open = true);
  ~PopUpMessageBox();
  void Update();

private:
  void CreateWindowText();

  std::string _text;
  WindowText* _winText;
};

