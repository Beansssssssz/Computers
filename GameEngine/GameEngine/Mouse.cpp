#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Mouse.hpp"


Mouse::Mouse(Vector2i pos)
{  
  cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
  if (cursor == NULL)
    std::cout << "mouse has failed to initialize. Error: " << SDL_GetError() << std::endl;
  SDL_SetCursor(cursor);
};


Mouse::~Mouse()
{
  SDL_FreeCursor(cursor);
}

Vector2i Mouse::GetPos()
{
    return pos;
}

ButtonPressed Mouse::GetPressed()
{
  return bt;
}

void Mouse::UpdatePos()
{
  bt = ButtonPressed(SDL_GetMouseState(&pos.x, &pos.y));
};

