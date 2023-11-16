#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Square {
public:
  Square(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect);
  ~Square();
  Vector2f& GetPos();
  SDL_Texture* GetTexture();
  SDL_Rect GetSrcRect();
  SDL_Rect GetDstRect();

protected:
  SDL_Texture* tex;
  SDL_Rect srcRect;
  SDL_Rect dstRect;
};
