#pragma once
#include <SDL.h>

#include "Button.hpp"
#include "Keyboard.hpp"
#include "WindowText.hpp"

class WelcomeScene {
public:
  WelcomeScene(SDL_Texture* tex, const char* fontpath, int textSize);
  ~WelcomeScene();
  void Update();
  bool IsKeyPressed();
  void SetKeyPressed(bool keyPressed);

private:
  Square* _bg;
  WindowText* _winText;
  bool _keyPressed;
};
