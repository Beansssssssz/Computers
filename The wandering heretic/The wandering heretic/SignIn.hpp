#pragma once

#include "TextSquare.hpp"
#include "PopUpWindow.hpp"
#include "Server.hpp"

enum class SignInSquares
{
  none = 0,
  email = 1,
  password = 2
};

class SignIn {
public:
  SignIn(Vector2i backgroundRect, Vector2i emailStartPos, int margin);
  ~SignIn();

  bool Update();
  UserData GetData();
  bool IsOpen();

private:
  void DisplaySquareNames();
  void DisplaySquareTitles();
  void SelectFlag();
  void UpdateCursor();
  void DisplayErrorMessage();
  bool UpdatedDoneButton();
  bool CheckIfDataIsValid();

  void CreateTextSquares(Vector2i& emailStartPos, int& margin);
  void CreateBackground(Vector2i backgroundPos, int margin);
  void CreateDoneButton();

  SignInSquares _currentSquare;
  TextSquare* _email; //can be or email or username
  TextSquare* _pass;
  Button* _doneBtn;

  PopUpWindow* _background;
  uint32_t _currentTimer;
  uint32_t _oldTimer;
  bool _nowDisplay;

  std::string _errorMsg;

  constexpr static uint16_t CURSOR_COUNTER = 500;
  constexpr static uint8_t MAX_LETTERS = 35;
  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static uint8_t TITLE_LETTER_SIZE = 30;

  constexpr static SDL_Color BACKGROUND_COLOR{ 0,0,0,170 };
  constexpr static SDL_Color BLACK_COLOR{ 0,0,0,255 };

  constexpr static SDL_Color ERROR_LETTER_COLOR{ 255,0,0,255 };
  constexpr static uint8_t ERROR_LETTER_SIZE = 10;
};

