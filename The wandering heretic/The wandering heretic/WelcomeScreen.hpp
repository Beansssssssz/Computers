#pragma once
#include <SDL.h>

#include "Button.hpp"
#include "Keyboard.hpp"
#include "WindowText.hpp"

class WelcomeScreen {
public:
  WelcomeScreen(const char* text, const char* fontpath, int textSize);
  ~WelcomeScreen();
  void Update();
  bool IsKeyPressed();
  void SetKeyPressed(bool keyPressed);

private:
  Square* _bg;
  WindowText* _winText;
  const char* _text;
  bool _keyPressed;
};
