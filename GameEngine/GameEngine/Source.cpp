#include <SDL.h>
#include <SDL_image.h>
#include <iostream>



int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) //if sdl_init return somthing greater than 0 then a prob has occured
    std::cout << "SDL Init failed. SDL ERROR: " << SDL_GetError() << std::endl;

  if(!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG Init failed. IMG ERROR: " << IMG_GetError() << std::endl;


  return 0;
}
