#pragma once

#include <SDL.h>


#include "Button.hpp"

class WelcomeScreen {
public:
  WelcomeScreen(SDL_Texture* buttonsTex, Vector2i exitPos, Vector2i StartPos);

private:
  Button* _btnExit;
  Button* _btnStart;
};
