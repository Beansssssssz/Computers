#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

//#including my own libs
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

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = NULL;
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;


int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;

  if (TTF_Init() < 0)
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;

  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) < 0)
    std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;

  RenderWindow* window = RenderWindow::GetRenderWindow();
  Mouse* mouse = Mouse::GetMouse();
  Keyboard* keyboard = Keyboard::GetKeyboard();

  SDL_Texture* tex = window->LoadTexture("Assets/backround_pic.png");
  SDL_Rect rect;
  rect.x = 0; rect.y = 0;
  RenderWindow::GetWidthHeight(rect.w, rect.h);
  Square backround(tex, rect, rect);

  tex = window->LoadTexture("Assets/GUI/btnExit.png");
  GameManager gm(tex, "Assets/Fonts/Sans.ttf");

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

    window->Render(backround);

    mouse->Update();
    keyboard->Update();

    gm.Update();

    window->Display();
  };

  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};
