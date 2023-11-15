#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
  :window(NULL), renderer(NULL)//sets the 2 vars to null
{
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (window == NULL)
    std::cout << "window failed to init. Error: " << SDL_GetError() << std::endl;

  //the -1 is saying to use whatever flags the programs needs to run
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);                                                            
  if(renderer == NULL)
    std::cout << "window failed to render. Error: " << SDL_GetError() << std::endl;
};

SDL_Texture* RenderWindow::LoadTexture(const char* filepath) {

  SDL_Texture* texture = NULL;
  texture = IMG_LoadTexture(renderer, filepath);

  if (texture == NULL)
    std::cout << "Texture faild to load. Error: " << SDL_GetError() << std::endl;

  return texture;
}

void RenderWindow::Display() {
  SDL_RenderPresent(renderer);
};

void RenderWindow::Render(Vector2f pos, SDL_Rect rect, SDL_Texture* tex) {

  //the src rect means how many pixels to tale from the texture
  SDL_Rect src;//src = SDL rect
  src.x = rect.x;
  src.y = rect.y;
  src.w = rect.w;
  src.h = rect.h;

  //the dst means where to put the texture on the window
  SDL_Rect dst;//src = SDL rect
  dst.x = pos.x;
  dst.y = pos.y;
  dst.w = rect.w;
  dst.h = rect.h;
  if(!(SDL_RenderCopy(renderer, tex, &src, &dst) == 0))
    std::cout << "Texture faild to be copied. Error: " << SDL_GetError() << std::endl;
};

void RenderWindow::Clear() {
  SDL_RenderClear(renderer);
};

RenderWindow::~RenderWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}
SDL_Window* RenderWindow::GetWindow()
{
  return window;
}
SDL_Renderer* RenderWindow::GetRenderer()
{
  return renderer;
}
;
