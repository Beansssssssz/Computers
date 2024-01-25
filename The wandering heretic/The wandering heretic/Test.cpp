//including my own libs
#include "GameManager.hpp"
#include "GIF.h"

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = NULL;
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;
Audio* Audio::_audioInstance = NULL;

int main(int argc, char* argv[]) {
  //initializing the libraries
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Init failed. SDL ERROR: %s", SDL_GetError());

  if (IMG_Init(IMG_INIT_PNG) == 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG Init failed. IMG ERROR: %s", IMG_GetError());

  if (TTF_Init() != 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_ttf: %s", TTF_GetError());

  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) == 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_mixer: %s", Mix_GetError());

  ////singletons
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Mouse* mouse = Mouse::GetMouseInstance();
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Audio* audio = Audio::GetAudioInstance();

  GameManager gm;

  bool running = true;
  SDL_Event event;


  //GIF(nullptr, { 0,0,0,0 }, {0,0,0,0}, 0);
  // i have local commit
  //starting the main loop
  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }

      keyboard->BuildText(event);
    }
    /*if (!window->IsWindowFocused())
      continue;*/

    window->Clear();

    mouse->Update();
    keyboard->Update();

    if (running && !gm.Update())//if the game is not going to be closed from events
      running = false;

    window->Display();

    utils::CapFPS(start, 60);
  };
  //deleting singletons
  delete window;
  delete mouse;
  delete keyboard;
  delete audio;

  //quit sdl services
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};

/*
TODO
NOW:
//square class->a basic square (no collisions)
//Entity class->sqaure with collisions(like floor or wall)
//basePlayer class -> a player class that can move left and right and jump has gravity
//baseEnemy class -> idk yet



//create the actually game
i am burnt out and need to do somthing fun in this project



//sign in -> after the game?

//OVERALL:
2.5 ->add a way to "freeze" stuff ->
a way to tell the mouse to stop the pressing on other buttons
or -> use the bool as a pointer or ref(ref better) and when u r updating the buttons
check if the settings is open.

3.settings -> change textures(when active and not active) and change quit btn texture;

4.learn sqlite3 -> how to send to main databse not local(use arduino to do it?)

5. multiplayer????

7.the game itself -> the games is built of rooms.
(like hollow knight rooms not mario like)
*/
