#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>
#include <pthread.h>

//including my own libs
#include "Square.hpp"
#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "Button.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"
#include "WindowText.hpp"
#include "Audio.hpp"
#include "PopUpWindow.hpp"
#include "GameManager.hpp"
#include "Slider.hpp"

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = NULL;
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;

int main(int argc, char* argv[]) {
  //initializing the libraries
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Init failed. SDL ERROR: %s", SDL_GetError());

  if (!(IMG_Init(IMG_INIT_PNG)))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG Init failed. IMG ERROR: %s", IMG_GetError());

  if (TTF_Init() < 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_ttf: %s", TTF_GetError());

  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) < 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_mixer: %s", Mix_GetError());

  //singletons
  RenderWindow* window = RenderWindow::GetRenderWindow();
  Mouse* mouse = Mouse::GetMouse();
  Keyboard* keyboard = Keyboard::GetKeyboard();

  GameManager gm;

  //starting the main loop
  bool running = true;
  SDL_Event event;
  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;

      keyboard->BuildText(event);
    }
    if (!window->IsWindowFocused())
      continue;

    window->Clear();

    mouse->Update();
    keyboard->Update();

    if (running && !gm.Update())//if the game is not going to be closed from events
      running = false;

    window->Display();

    utils::CapFPS(start, 60);
  };

  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};


/*
TODO
2.about // changed to creating a a texture with a x button to close or esc.
3.settings // add a slider and on of for music
4.sign in //kill me
5.learn sql // double it
5.the game itself //fun ☺
*/
