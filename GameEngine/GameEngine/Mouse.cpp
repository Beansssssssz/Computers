#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Mouse.hpp"


Mouse::Mouse(Vector2i pos)
  :current(SDL_SYSTEM_CURSOR_ARROW)
{
  cursor = SDL_CreateSystemCursor(current);
  if (cursor == NULL)
    std::cout << "mouse has failed to initialize. Error: " << SDL_GetError() << std::endl;
  SDL_SetCursor(cursor);
};


Mouse::~Mouse()
{
  SDL_FreeCursor(cursor);
};

Vector2i Mouse::GetPos()
{
  return pos;
};

MouseButtons Mouse::GetPressed()
{
  return bt;
};

void Mouse::UpdatePos()
{
  bt = MouseButtons(SDL_GetMouseState(&pos.x, &pos.y));
};

void Mouse::ChangeCursorType(bool isSelecting)
{
  SDL_FreeCursor(cursor);

  if (isSelecting)
    current = SDL_SYSTEM_CURSOR_HAND;
  else
    current = SDL_SYSTEM_CURSOR_ARROW;

  cursor = SDL_CreateSystemCursor(current);
  SDL_SetCursor(cursor);
};



