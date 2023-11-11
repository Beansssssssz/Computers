#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
//#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Square.hpp"

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) //if sdl_init return somthing greater than 0 then a prob has occured
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if(!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;

  const int width = 1920, height = 1080;

  RenderWindow window("game", width, height);
    
  SDL_Texture* grassTexture = window.LoadTexture("Assets/ground_grass1.png");

  std::vector<Square> platforms;
    
  //the i-1 is there because the window isnt always perfect and sometimes there are still platforms missing
  //so the -1 is addign another platform so it would all be there.
  for (float i = 0; i - 1 < width / 128; i++) {
    Vector2f pos(i* 128, height - 128);
    SDL_Rect rect;
    rect.x = 0; rect.y = 0, rect.w = 128; rect.h = 128;
    platforms.push_back(Square(pos, grassTexture, rect));
  }

  bool running = true;
  SDL_Event event; //the window event(like close,minize,keypress)

  const float maxFPS = 120;
  int counter = 0;


  while (running) {
    float start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
    }
    window.Clear();

    for (int i = 0; i < platforms.size(); i++) 
      window.Render(platforms[i]);

    window.Display();

    //utils::CapFPS(start, maxFPS);
    utils::GetFPS(start);
  }

  SDL_Quit();
  return 0;
}
