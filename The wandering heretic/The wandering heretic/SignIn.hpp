#pragma once

#include "TextSquare.hpp"
#include "PopUpWindow.hpp"

enum class Squares
{
  none = 0,
  email = 1,
  password = 1
};

class SignIn
{
public:
  SignIn(Vector2i backgroundRect, Vector2i emailStartPos, int margin);
  ~SignIn();

  void Update();
  void GetData(std::string* email, std::string* password);

private:
  void DisplaySquareNames();
  void SelectFlag();
  void UpdateCursor();
  bool UpdatedDoneButton();

  void CreateTextSquares(Vector2i& emailStartPos, int& margin);
  void CreateBackground(Vector2i backgroundPos, int margin);
  void CreateDoneButton();

  Squares _currentSquare;
  TextSquare* _email; //can be or email or username
  TextSquare* _pass;
  Button* _doneBtn;

  PopUpWindow* _background;
  uint32_t currentTimer;
  uint32_t _oldTimer;
  bool _nowDisplay;

  constexpr static uint16_t CURSOR_COUNTER = 500;
  constexpr static uint8_t MAX_LETTERS = 35;
  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static SDL_Color BACKGROUND_COLOR{ 255,0,0,255 };
  constexpr static SDL_Color BLACK_COLOR{ 0,0,0,255 };
};

