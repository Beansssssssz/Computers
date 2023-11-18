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
#include "Keyboard.hpp"

std::vector<Square> CreatePlatforms(int w, int h, SDL_Texture* tex);
Button CreateButton(SDL_Texture* tex, int w, int h, Vector2i pos);

int main(int argc, char* argv[]) {

  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if(!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;

  const int width = 1920, height = 1080, gravity = 10;
  RenderWindow window("game", width, height);
    
  SDL_Texture* tex = window.LoadTexture("Assets/ground_grass1.png");

  std::vector<Square> platforms = CreatePlatforms(width, height, tex);

  Vector2i pos(0, 0);
  Mouse mouse(pos);

  Keyboard keyboard;
  
  tex = window.LoadTexture("Assets/button_UI.png");
  Button button = CreateButton(tex, 160, 160, Vector2i(4, 1));

  SDL_Rect rect;
  rect.x = width - 300; rect.y = 0, rect.w = 300; rect.h = 300;

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
    keyboard.Update();

    for (int i = 0; i < platforms.size(); i++)  
      window.Render(platforms[i].GetTexture(), platforms[i].GetDstRect(), platforms[i].GetSrcRect());

    window.Render(button.GetTexture(), button.GetDstRect(), button.GetSrcRect());

    RGBA color(40, 100, 100, 255);
    window.CreateRect(&rect, color);

    if(keyboard.GetKeyArray()[SDL_SCANCODE_S])
    for (int i = 0; i < platforms.size(); i++)
      if (rect.y < height && !platforms[i].IsColliding(rect)) {
        rect.y++;
        break;
      }



    if (keyboard.GetKeyArray()[SDL_SCANCODE_W])
      rect.y--;
    if (keyboard.GetKeyArray()[SDL_SCANCODE_A])
      rect.x--;
    if (keyboard.GetKeyArray()[SDL_SCANCODE_D])
      rect.x++;

    button.Update(mouse, MouseButtons::mbl);
    if (button.GetIsPressed())
      running = false;

    window.Display();

    //utils::CapFPS(start, 60);
    //utils::GetFPS(start);
  }

  SDL_Quit();
  return 0;
}

Button CreateButton(SDL_Texture* tex, int w, int h, Vector2i pos) {
  SDL_Rect srcRect, dstRect;
  dstRect.x = 0; dstRect.y = 0, dstRect.w = w; dstRect.h = h;
  srcRect.x = w * pos.x; srcRect.y = h * pos.y, srcRect.w = w; srcRect.h = h;
  Button button(tex, srcRect, dstRect);

  return button;
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
    platforms.push_back(Square(tex, srcRect, dstRect, true));//we need the platforms to have collision
  }

  return platforms;
}
