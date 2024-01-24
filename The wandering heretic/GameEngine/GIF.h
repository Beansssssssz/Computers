#pragma once

#include <SDL.h>
#include<SDL_image.h>

class GIF
{
public:
  GIF(SDL_Texture** texs, SDL_Rect srcrect, SDL_Rect dstrect);

private:
  SDL_Texture** _texs;
};

