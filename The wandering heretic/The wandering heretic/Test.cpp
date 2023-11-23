#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Square.hpp"
#include "Mouse.hpp"
#include "Button.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"
#include "WindowText.hpp"
#include"Audio.hpp"


std::vector<Square> CreatePlatforms(int w, int h, SDL_Texture* tex);
Button CreateButton(SDL_Texture* tex, int w, int h, Vector2i pos);
//void CreateSignWindow(const char* text, Keyboard keyboard, RenderWindow window);


int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;

  if (TTF_Init() < 0)
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;

  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) < 0)
    std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;

  const int width = 1920, height = 1080, gravity = 10;
  RenderWindow window("game", width, height);

  SDL_Texture* tex = window.LoadTexture("Assets/ground_grass1.png");

  std::vector<Square> platforms = CreatePlatforms(width, height, tex);
  tex = window.LoadTexture("Assets/backround_pic.png");

  SDL_Rect rect;
  rect.x = 0; rect.y = 0, rect.w = width; rect.h = height;
  Square backround(tex, rect, rect);

  Vector2i pos(0, 0);
  Mouse mouse(pos);

  Keyboard keyboard;

  tex = window.LoadTexture("Assets/button_UI.png");
  Button button = CreateButton(tex, 160, 160, Vector2i(4, 1));

  WindowText winText("Assets/Fonts/Sans.ttf", 40, "aaaaaaaaaa");

  rect.x = 700; rect.y = 500, rect.w = 20; rect.h = 20;

  bool listen = false;

  bool running = true;
  SDL_Event event; //the window event(like close, minize, keypress)

  Audio audio("Assets/Sounds/ahem_x.wav");

  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
      keyboard.BuildText(event);
    }
    window.Clear();

    mouse.UpdatePos();
    keyboard.Update();

    window.Render(backround.GetTexture(), backround.GetSrcRect(), backround.GetDstRect());

    for (int i = 0; i < platforms.size(); i++)
      window.Render(platforms[i].GetTexture(), platforms[i].GetSrcRect(), platforms[i].GetDstRect());

    window.Render(button.GetTexture(), button.GetSrcRect(), button.GetDstRect());

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

    SDL_Rect rect1;
    rect1.x = 300; rect1.y = 300, rect1.w = 500; rect1.h = 500;
    RGBA color(40, 80, 100, 160);
    window.CreateRect(&rect1, color);

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
  srcRect.x = w * pos.x; srcRect.y = h * pos.y, srcRect.w = w; srcRect.h = h;
  Button button(tex, srcRect, dstRect);

  return button;
};

std::vector<Square> CreatePlatforms(int w, int h, SDL_Texture* tex) {
  //the i-1 is there because the window isnt always perfect and sometimes there are still platforms missing
  //so the -1 is addign another platform so it would all be there.
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

void CreateSignWindow(const char* text, Keyboard keyboard, RenderWindow* window) {


}
