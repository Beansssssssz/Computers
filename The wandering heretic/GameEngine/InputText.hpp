#pragma once

#include <string>
#include "Math.hpp"
#include "WindowText.hpp"

class InputText
{
public:
  InputText(std::string example, Vector2i pos);
  ~InputText();

  void Update(bool input = true);

  std::string GetText();
  const int GetSquareWidth();
  const int GetSquareHeight();
  Vector2i* GetPos();
  const SDL_Rect GetRvalueRect();
private:
  void DisplayRect();
  void DisplayText(bool input);
  void DisplayFlashingCursor();


  WindowText* _winText;

  std::string _text; // the text to to display
  std::string _exampleText; //the text to display to explaine

  Vector2i _pos; //the pos where to start printing out the text
  const int WIDTH;
  const int HEIGHT;

  Uint32 timer;
  Uint32 counter;
};
