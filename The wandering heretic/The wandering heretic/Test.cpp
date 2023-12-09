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

//initializing functions
void InfiniteThreadLoop(void* FuncPtr);

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Init failed. SDL ERROR: %s", SDL_GetError());

  if (!(IMG_Init(IMG_INIT_PNG)))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG Init failed. IMG ERROR: %s", IMG_GetError());

  if (TTF_Init() < 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_ttf: %s", TTF_GetError());

  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) < 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_mixer: %s", Mix_GetError());


  RenderWindow* window = RenderWindow::GetRenderWindow();
  Mouse* mouse = Mouse::GetMouse();
  Keyboard* keyboard = Keyboard::GetKeyboard();

  SDL_Texture* tex = window->LoadTexture("Assets/backround_pic.png");
  SDL_Rect rect;
  RenderWindow::GetWidthHeight(rect.w, rect.h);
  Square backround(tex, rect, rect);

  tex = utils::GetTexture(1);
  GameManager gm(tex, "Assets/Fonts/Sans.ttf");

  /*
  rect.x = 200; rect.y = 200; rect.w = 20; rect.h = 30;
  Slider test(rect, 100, 300, RGBA(0, 0, 255, 255), 10);
  WelcomeScene* _wcScene = new WelcomeScene(tex, "aaaaaaaaaaa", "Assets/Fonts/Sans.ttf", 24);
  */

  bool running = true;
  SDL_Event event;

  bool focused = true;

  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
      //if()
      //if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        //gm.GetPopUpWindow().OpenTab();

      keyboard->BuildText(event);
    }
    focused = window->IsWindowFocused();
    if (!focused)
      continue;

    window->Clear();

    //window->Render(backround);

    mouse->Update();
    keyboard->Update();

    //only for testing
    {
      //test.Update();
      //_wcScene->Update();
    }

    gm.Update();

    window->Display();
    
  };

  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};
