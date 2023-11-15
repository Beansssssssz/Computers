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
Button CreateButton(SDL_Texture* tex, int w, int h);

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
  Button button = CreateButton(tex, 160, 160);

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

    for (int i = 0; i < platforms.size(); i++) 
      window.Render(platforms[i].GetPos(), platforms[i].GetRect(), platforms[i].GetTexture());


    mouse.UpdatePos();

    window.Render(button.GetPos(), button.GetRect(), button.GetTexture());

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

Button CreateButton(SDL_Texture* tex, int w, int h) {
  //just a rand button for testing
  Vector2f pos1(1920 / 2, 1080 / 2);
  SDL_Rect rect;
  rect.x = 160; rect.y = 0, rect.w = w; rect.h = h;
  Button button(pos1, tex, rect);

  return button;
}



std::vector<Square> CreatePlatforms(int w,int h, SDL_Texture* tex) {
  //the i-1 is there because the window isnt always perfect and sometimes there are still platforms missing
  //so the -1 is addign another platform so it would all be there.
  std::vector<Square> platforms;
  SDL_Rect rect;
  rect.x = 0; rect.y = 0, rect.w = 128; rect.h = 128;
  for (float i = 0; i - 1 < w / 128; i++) {
    Vector2f pos(i * 128, h - 128);
    platforms.push_back(Square(pos, tex, rect));
  }

  return platforms;
}
