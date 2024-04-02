#pragma once
#include <TextSquare.hpp>

#define EMAIL_FLAG 1
#define USERNAME_FLAG 2
#define PASSWORD_FLAG 3
#define PASSWORD_CONFIRM_FLAG 4

class SignUp
{
public:
  SignUp(SDL_Rect backgroundRect, Vector2i emailStartPos, int margin);
  ~SignUp();

private:
  void CreateTextSquares();
  bool IsMailValid(std::string& mail);
  bool IsPasswordStrong(std::string& password);
  bool IsLetterSpecial(const char& letter);
 
  

  uint8_t _currentFlag;
  TextSquare* _email;
  TextSquare* _username;
  TextSquare* _password;
  TextSquare* _passwordConfirm;
};

