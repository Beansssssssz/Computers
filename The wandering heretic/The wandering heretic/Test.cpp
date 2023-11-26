#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

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
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;

std::vector<Square> CreatePlatforms(SDL_Texture* tex);

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;

  if (TTF_Init() < 0)
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;

  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) < 0)
    std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;

  RenderWindow window("Game");

  SDL_Texture* tex = window.LoadTexture("Assets/backround_pic.png");
  SDL_Rect rect;
  rect.x = 0; rect.y = 0;
  RenderWindow::GetWidthHeight(rect.w, rect.h);
  Square backround(tex, rect, rect);

  Mouse* mouse = Mouse::GetMouse();

  Keyboard* keyboard = Keyboard::GetKeyboard();

  tex = window.LoadTexture("Assets/GUI/btnExit.png");
  //GameManager gm(tex, "Assets/Fonts/Sans.ttf");

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
    focused = window.IsWindowFocused();
    if (!focused)
      continue;

    window.Clear();

    window.Render(backround);

    mouse->Update();
    keyboard->Update();

    //gm.Update(&window);

    window.Display();
  };

  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};

std::vector<Square> CreatePlatforms(SDL_Texture* tex) {
  //the i-1 is there because the window isnt always perfect and sometimes there are still platforms missing
  //so the -1 is addign another platform so it would all be there.
  int w, h;
  RenderWindow::GetWidthHeight(w, h);

  std::vector<Square> platforms;
  SDL_Rect dstRect, srcRect;
  srcRect.x = 0; srcRect.y = 0, srcRect.w = 128; srcRect.h = 128;
  dstRect.x = 300; dstRect.y = 300; dstRect.w = 128, dstRect.h = 128;

  platforms.push_back(Square(tex, srcRect, dstRect, true));

  //for (int i = 0; i - 1 < w / 128; i++) {
  //  dstRect.x = i * dstRect.w; dstRect.y = h - dstRect.w;
  //  platforms.push_back(Square(tex, srcRect, dstRect, true));//we need the platforms to have collision
  //}

  return platforms;
};
