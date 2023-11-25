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


//initializing singletons
Mouse* Mouse::_mousePtr = NULL;

std::vector<Square> CreatePlatforms(SDL_Texture* tex);
Button CreateButton(SDL_Texture* tex, int w, int h, Vector2i pos);

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

  SDL_Texture* tex = window.LoadTexture("Assets/ground_grass1.png");

  std::vector<Square> platforms = CreatePlatforms(tex);
  tex = window.LoadTexture("Assets/backround_pic.png");

  SDL_Rect rect;
  rect.x = 0; rect.y = 0, rect.w = 1920; rect.h = 1080;
  Square backround(tex, rect, rect);

  Mouse* mouse = Mouse::GetMouse();

  Keyboard keyboard;

  tex = window.LoadTexture("Assets/GUI/btnExit.png");
  Button button = CreateButton(tex, 113, 114, Vector2i(2, 1));

  WindowText winText("Assets/Fonts/Sans.ttf", 40, "aaaaaaaaaa");

  rect.x = 700; rect.y = 500, rect.w = 20; rect.h = 20;

  bool listen = false;

  bool running = true;
  SDL_Event event; //the window event(like close, minize, keypress)

  Audio audio("Assets/Sounds/ahem_x.wav");

  SDL_Rect rect1;
  rect1.x = 300; rect1.y = 300, rect1.w = 500; rect1.h = 500;
  RGBA color(40, 80, 100, 160);
  Button button1 = CreateButton(tex, 113, 114, Vector2i(2, 1));

  PopUpWindow tab(button1, rect1, color, true);

  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
      keyboard.BuildText(event);
    }
    window.Clear();

    mouse->Update();
    keyboard.Update();

    //window.Render(backround.GetTexture(), backround.GetSrcRect(), backround.GetDstRect());
    window.Render(Square(backround));

    for (int i = 0; i < platforms.size(); i++)
      window.Render(Square(platforms[i]));
      //platforms[i].GetTexture(), platforms[i].GetSrcRect(), platforms[i].GetDstRect());

    //button.RenderSquare(&window);
    //window.Render(button.GetTexture(), button.GetSrcRect(), button.GetDstRect());
    window.Render(Square(button));

    //Creating the rect(or testing player)
    {
      RGBA color(255, 0, 0, 255);
      window.CreateRect(&rect, color);
    }

    //Player Movment Text
    {
      //SDL_Rect old = rect;

      if (keyboard.GetKeyArray()[SDL_SCANCODE_S]) {
        rect.y++;
        for (int i = 0; i < platforms.size(); i++)
          if (platforms[i].IsColliding(rect))
            rect.y--;
      }

      if (keyboard.GetKeyArray()[SDL_SCANCODE_SPACE]) {
        rect.y--;
        for (int i = 0; i < platforms.size(); i++)
          if (platforms[i].IsColliding(rect))
            rect.y++;
      }

      if (keyboard.GetKeyArray()[SDL_SCANCODE_A]) {
        rect.x--;
        for (int i = 0; i < platforms.size(); i++)
          if (platforms[i].IsColliding(rect))
            rect.x++;
      }

      if (keyboard.GetKeyArray()[SDL_SCANCODE_D]) {
        rect.x++;
        for (int i = 0; i < platforms.size(); i++)
          if (platforms[i].IsColliding(rect))
            rect.x--;
      }
    }

    //Text Input Text
    {
      if (keyboard.GetKeyArray()[SDL_SCANCODE_B] || listen) {
        listen = true;
        keyboard.StartBuildText();
        audio.PauseMusic();
      }
      if (keyboard.GetKeyArray()[SDL_SCANCODE_X] && listen) {
        listen = false;
        keyboard.StopBuildText(false);
        audio.ResumeMusic();
      }
    }

    button.Update(mouse, MouseButtons::mbl);
    if (button.GetIsPressed())
      running = false;

    winText.SetText(keyboard.GetText());
    winText.DisplayText(&window, Vector2i(500, 500), RGBA(0, 0, 0, 0));

    tab.Update(&window);

    //utils::CapFPS(start, 60);
    //utils::GetFPS(start);

    window.Display();
  };

  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};

Button CreateButton(SDL_Texture* tex, int w, int h, Vector2i pos) {
  SDL_Rect srcRect, dstRect;
  dstRect.x = 0; dstRect.y = 0, dstRect.w = w; dstRect.h = h;
  srcRect.x = 0; srcRect.y = 0, srcRect.w = w; srcRect.h = h;
  Button button(tex, srcRect, dstRect);

  return button;
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
