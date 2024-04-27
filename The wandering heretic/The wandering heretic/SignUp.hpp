#pragma once

#include "TextSquare.hpp"
#include "PopUpWindow.hpp"
#include "Server.hpp"

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
  UserData GetData();

private:
  void DisplaySquareNames();
  void DisplaySquareTitles();
  void SelectFlag();
  void UpdateCursor();
  void DisplayErrorMessage();
  bool UpdatedDoneButton();

  bool IsUserNameValid(std::string& username);
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

  std::string _errorMsg;

  constexpr static uint16_t CURSOR_COUNTER = 500;
  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static uint8_t TITLE_LETTER_SIZE = 30;
  constexpr static uint8_t MAX_LETTERS = 35;

  constexpr static SDL_Color BACKGROUND_COLOR{ 0,0,0,170 };
  constexpr static SDL_Color BLACK_COLOR{ 0,0,0,255 };

  constexpr static SDL_Color ERROR_LETTER_COLOR{ 255,0,0,255 };
  constexpr static uint8_t ERROR_LETTER_SIZE = 10;
};

