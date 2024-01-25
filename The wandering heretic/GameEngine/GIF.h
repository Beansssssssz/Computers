#pragma once

#include <SDL.h>
#include<SDL_image.h>

class GIF
{
public:
  GIF(SDL_Texture** texs, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay);


private:
  void ThreadCodeSegment();

  SDL_Texture** _texs;
};

