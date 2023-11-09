#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height)
  :window(NULL), renderer(NULL)//sets the 2 vars to null
{
  window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);
  if (window == NULL)
    std::cout << "window failed to init. Error: " << SDL_GetError() << std::endl;

  //the -1 is saying to initialize the required flags,saying opengl to use the gpu is its faster
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);                                                            
  if(renderer == NULL)
    std::cout << "window failed to render. Error: " << SDL_GetError() << std::endl;
};

SDL_Texture* RenderWindow::LoadTexture(const char* p_filepath) {

  SDL_Texture* texture = NULL;
  texture = IMG_LoadTexture(renderer, p_filepath);

  if (texture == NULL)
    std::cout << "Texture faild to load. Error: " << SDL_GetError() << std::endl;

  return texture;
}



RenderWindow::~RenderWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  std::cout << "worked :)" << std::endl;
};
