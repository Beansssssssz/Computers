#include <SDL.h>

#include "WelcomeScreen.hpp"

WelcomeScreen::WelcomeScreen()
:pressedKey(false),  btnPlay(NULL)
{
  SDL_Rect rect1, rect2;
  //btnPlay = *(Button::CreateButton(NULL, rect1, rect2));
};
  
WelcomeScreen::~WelcomeScreen()
{

};
