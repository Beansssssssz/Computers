#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Square.hpp"
#include "Mouse.hpp"
#include "Button.hpp"
#include "Math.hpp"
#include "Utils.hpp"

std::vector<Square> CreatePlatforms(int w, int h, SDL_Texture* tex);

int main(int argc, char* argv[]) {

  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if(!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;

  const int width = 1920, height = 1080;
  RenderWindow window("game", width, height);
    
  SDL_Texture* tex = window.LoadTexture("Assets/ground_grass1.png");

  std::vector<Square> platforms = CreatePlatforms(width, height, tex);

  Vector2i pos(0, 0);
  Mouse mouse(pos);
  
  tex = window.LoadTexture("Assets/button_UI.png");
  SDL_Rect srcRect, dstRect;
  dstRect.x = 0; dstRect.y = 0, dstRect.w = 160; dstRect.h = 160;
  srcRect.x = 160 * 4; srcRect.y = 160, srcRect.w = 160; srcRect.h = 160;
  
  Button button(tex, srcRect, dstRect);

  bool running = true;
  SDL_Event event; //the window event(like close, minize, keypress)

  while (running) {
    float start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
    }
    window.Clear();

    mouse.UpdatePos();

    //start of layer 1
    for (int i = 0; i < platforms.size(); i++)  
      window.Render(platforms[i].GetTexture(), platforms[i].GetDstRect(), platforms[i].GetSrcRect());
    //end of layer 1

    //start of layer 2
    window.Render(button.GetTexture(), button.GetDstRect(), button.GetSrcRect());
    //end of layer 2

    button.Update(mouse, ButtonPressed::mbl);
    if (button.GetIsPressed())
      running = false;

    window.Display();

    //utils::CapFPS(start, maxFPS);
    //utils::GetFPS(start);
  }

  SDL_Quit();
  return 0;
}

std::vector<Square> CreatePlatforms(int w, int h, SDL_Texture* tex) {
  //the i-1 is there because the window isnt always perfect and sometimes there are still platforms missing
  //so the -1 is addign another platform so it would all be there.
  std::vector<Square> platforms;
  SDL_Rect dstRect , srcRect;
  srcRect.x = 0; srcRect.y = 0, srcRect.w = 128; srcRect.h = 128;
  dstRect.w = 128, dstRect.h = 128;
  for (float i = 0; i - 1 < w / 128; i++) {
    dstRect.x = i * dstRect.w; dstRect.y = h - dstRect.w;
    platforms.push_back(Square(tex, srcRect, dstRect));
  }

  return platforms;
}