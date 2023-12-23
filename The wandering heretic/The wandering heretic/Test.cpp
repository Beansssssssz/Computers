#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>

//including my own libs
#include "GameManager.hpp"//everything is inside GameManager.
#include "Setting.hpp"

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = NULL;
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;
Audio* Audio::_audioInstance = NULL;


Settings* CreateSettings(int marginx = 500, int marginy = 300);

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

  //singletons
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Mouse* mouse = Mouse::GetMouseInstance();
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Audio* audio = Audio::GetAudioInstance();

  GameManager gm;
  Settings* st = CreateSettings();
  st->OpenTab();

  bool running = true;
  SDL_Event event;

  //starting the main loop
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

    st->Update();

    window->Display();

    utils::CapFPS(start, 60);
  };

  //deleting singletons
  delete window, mouse, keyboard, audio;
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};

Settings* CreateSettings(int marginx, int marginy) {
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/Xbtn.png");
  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);
  Button* btn = new Button(tex, { 0,0,w,h }, { 0,0,w,h });

  SDL_Color _color{ 255,100,100,100 };

  SDL_Rect rect;
  RenderWindow::GetWidthHeight(w, h);
  rect.x = marginx;
  rect.y = marginy;
  rect.w = w - marginx * 2;
  rect.h = h - marginy * 2;


  Settings* st = new Settings(btn, rect, _color);

  return  st;
}

/*
TODO
2.enter doesnt work(why idk check it)
3.settings ->add the slider and correct pictures and correct placements
4.sign in //kill me(later, wayyyy later)
5.learn sqlite3 -> how to send to main databse not local(use arduino to do it?)
5.the game itself //fun ☺
*/
