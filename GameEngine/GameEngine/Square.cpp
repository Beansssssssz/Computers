#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Square.hpp"

Square::Square(Vector2f vec, SDL_Texture* tex, SDL_Rect& rect)
  :pos(pos), tex(tex), CurrentFrame(rect)
{
  std::cout << rect.w << std::endl;
  std::cout << rect.h << std::endl;
}

Square::~Square()
{}

Vector2f& Square::GetPos()
{
  return pos;
}

SDL_Texture* Square::GetTexture()
{
  return tex;
}

SDL_Rect Square::GetCurrentFrame()
{
  return CurrentFrame;
}
