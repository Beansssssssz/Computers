#pragma once

#include "TextSquare.hpp"
#include "PopUpWindow.hpp"

#define EMAIL_FLAG 1
#define USERNAME_FLAG 2
#define PASSWORD_FLAG 3
#define PASSWORD_CONFIRM_FLAG 4

class SignUp
{
public:
  SignUp(Vector2i backgroundPos, Vector2i emailStartPos, int margin);
  ~SignUp();

  void Update();
private:
  void DisplaySquareNames();
  void SelectFlag();

  bool IsMailValid(std::string& mail);
  bool IsPasswordStrong(std::string& password);
  bool IsLetterSpecial(const char& letter);

  void CreateBackground(Vector2i backgroundPos, int margin);
  void CreateTextSquares(Vector2i emailStartPos, int margin);
 
  uint8_t _currentSquare;
  TextSquare* _email;
  TextSquare* _username;
  TextSquare* _password;
  TextSquare* _passwordConfirm;

  PopUpWindow* _background;

  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static uint8_t MAX_LETTERS = 35;
  constexpr static SDL_Color BACKGROUND_COLOR{ 255,0,0,255 };
};

