#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) //if sdl_init return somthing greater than 0 then a prob has occured
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if(!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;

  RenderWindow window("game", 600, 400);

  SDL_Texture* grassTexture = window.LoadTexture("ground_grass1.png");

  bool running = true;
  SDL_Event event; //the window event(like close,minize,keypress)

  while (running) {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
    }
  }

  SDL_Quit();
  return 0;
}
