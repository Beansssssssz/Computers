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
  SignUp(SDL_Rect backgroundRect, Vector2i emailStartPos, int margin);
  ~SignUp();

  void Update();
private:
  void SelectFlag();

  bool IsMailValid(std::string& mail);
  bool IsPasswordStrong(std::string& password);
  bool IsLetterSpecial(const char& letter);

  void CreateBackground(SDL_Rect backgroundRect);
  void CreateTextSquares(Vector2i emailStartPos, int margin);
 
  uint8_t _currentFlag;
  TextSquare* _email;
  TextSquare* _username;
  TextSquare* _password;
  TextSquare* _passwordConfirm;

  PopUpWindow* _background;

  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static uint8_t MAX_LETTERS = 30;
  constexpr static SDL_Color BACKGROUND_COLOR{ 255,0,0,255 };
};

