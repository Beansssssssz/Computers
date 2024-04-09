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
 
  SignUpSquares _currentSquare;
  TextSquare* _email;
  TextSquare* _username;
  TextSquare* _password;
  TextSquare* _passwordConfirm;

  PopUpWindow* _background;
  

  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static uint8_t MAX_LETTERS = 35;
  constexpr static SDL_Color BACKGROUND_COLOR{ 255,0,0,255 };
};

