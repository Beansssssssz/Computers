#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Square {
public:
  Square(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect, bool collisionEnabled = false);
  ~Square();
  Vector2f& GetPos();
  SDL_Texture* GetTexture();
  void SetTexture(SDL_Texture* texture);
  SDL_Rect* GetSrcRect();
  SDL_Rect GetDstRect();
  bool IsColliding(SDL_Rect& rect);

protected:
  SDL_Texture* tex;
  SDL_Rect srcRect;
  SDL_Rect dstRect;
  bool collisionEnabled = false;
};
