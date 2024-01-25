#include "GIF.h"

#include <iostream>
#include <SDL_thread.h>


int thread_func(void* unused);

typedef struct {
  SDL_Texture** texs;
  SDL_Rect srcrect;
  SDL_Rect dstrect;
  uint32_t delay;
}GIFInfo;


GIF::GIF(SDL_Texture** texs, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay)
{
  GIFInfo* info = (GIFInfo*)malloc(sizeof(GIFInfo));
    
  info->texs = texs;
  info->srcrect = srcrect;
  info->dstrect = dstrect;
  info->delay = delay;

  SDL_Thread* th;
  th = SDL_CreateThread(thread_func, "hey", ((void*)info));
}

int thread_func(void* unused)
{
  GIFInfo* info = (GIFInfo*)unused;

  while (1) {
    std::cout << info->delay << '\n';
    SDL_Delay(100);
  }
    

  free(info);
  return(0);
}
