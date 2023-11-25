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
  delete _mousePtr;
}
Mouse* Mouse::GetMouse()
{
  if (_mousePtr == NULL)
  {
    Vector2i pos(0, 0);
    _mousePtr = new Mouse(pos);
    return _mousePtr;
  }
  else
    return _mousePtr;
};

Vector2i Mouse::GetPos()
{
  return pos;
};

MouseButtons Mouse::GetPressed()
{
  return bt;
}
void Mouse::Update()
{
  UpdatePos();
  ChangeCursorType();

  _mouseSelecting = false;//setting up for the next frame
};

void Mouse::UpdatePos()
{
  bt = MouseButtons(SDL_GetMouseState(&pos.x, &pos.y));
};

void Mouse::ChangeCursorType()
{
  SDL_SystemCursor old = current;

  if (_mouseSelecting)
    current = SDL_SYSTEM_CURSOR_HAND;
  else
    current = SDL_SYSTEM_CURSOR_ARROW;

  if (current != old) {
    SDL_FreeCursor(cursor);
    cursor = SDL_CreateSystemCursor(current);
    SDL_SetCursor(cursor);
  }
};

void Mouse::MouseIsSelecting()
{
  this->_mouseSelecting = true;
};



