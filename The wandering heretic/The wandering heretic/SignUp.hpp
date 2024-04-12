#pragma once

#include "TextSquare.hpp"
#include "PopUpWindow.hpp"

enum class SignUpSquares
{
  none = 0,
  email = 1,
  username = 2,
  password = 3,
  passwordConfirm = 4
};

class SignUp {
public:
  SignUp(Vector2i backgroundPos, Vector2i emailStartPos, int margin);
  ~SignUp();

  bool Update();
  void GetData(std::string* email, std::string* username, std::string* password);

private:
  void DisplaySquareNames();
  void SelectFlag();
  void UpdateCursor();
  bool UpdatedDoneButton();

  bool IsMailValid(std::string& mail);
  bool IsPasswordStrong(std::string& password);
  bool IsLetterSpecial(const char& letter);

  void CreateBackground(Vector2i backgroundPos, int margin);
  void CreateTextSquares(Vector2i emailStartPos, int margin);
  void CreateDoneButton();
 
  SignUpSquares _currentSquare;
  TextSquare* _email;
  TextSquare* _username;
  TextSquare* _password;
  TextSquare* _passwordConfirm;
  Button* _doneBtn;

  PopUpWindow* _background;
  uint32_t _currentTimer;
  uint32_t _oldTimer;
  bool _nowDisplay;

  constexpr static uint16_t CURSOR_COUNTER = 500;
  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static uint8_t MAX_LETTERS = 35;
  constexpr static SDL_Color BACKGROUND_COLOR{ 255,0,0,255 };
  constexpr static SDL_Color BLACK_COLOR{ 0,0,0,255 };
};

