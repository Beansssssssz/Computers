#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

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

void RenderWindow::Render(Entity& entity) {

  SDL_Rect src;//src = SDL rect
  src.x = entity.GetCurrentFrame().x;
  src.y = entity.GetCurrentFrame().y;
  src.w = entity.GetCurrentFrame().w;
  src.h = entity.GetCurrentFrame().h;

  SDL_Rect dst;//src = SDL rect
  dst.x = entity.GetPos().x;
  dst.y = entity.GetPos().y;
  dst.w = entity.GetCurrentFrame().w * 4;
  dst.h = entity.GetCurrentFrame().h * 4;
  SDL_RenderCopy(renderer, entity.GetTexture(), &src, &dst);
};

void RenderWindow::Clear() {
  SDL_RenderClear(renderer);
};

RenderWindow::~RenderWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
};
