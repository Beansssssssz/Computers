#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Mouse.hpp"
#include "Utils.hpp"

Mouse::Mouse(Vector2i _pos)
  :_current(SDL_SYSTEM_CURSOR_ARROW), _isFrozen(false), _mouseSelecting(false)
{
  _cursor = SDL_CreateSystemCursor(_current);
  if (_cursor == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "mouse has failed to initialize.");
  SDL_SetCursor(_cursor);
};

Mouse::~Mouse()
{
  SDL_FreeCursor(_cursor);
};

Mouse* Mouse::GetMouseInstance()
{
  if (_mousePtr == NULL)
    _mousePtr = new Mouse(Vector2i{ 0,0 });
  return _mousePtr;
};

Vector2i Mouse::GetPos()
{
  return _pos;
};

MouseButtons Mouse::GetPressed()
{
  return bt;
}
void Mouse::Update()
{
  bt = MouseButtons(SDL_GetMouseState(&_pos.x, &_pos.y));
  ChangeCursorType();

  _mouseSelecting = false;//setting up for the next frame
};

void Mouse::ChangeCursorType()
{
  if (_isFrozen)
    return;

  SDL_SystemCursor old = _current;

  if (_mouseSelecting)
    _current = SDL_SYSTEM_CURSOR_HAND;
  else
    _current = SDL_SYSTEM_CURSOR_ARROW;

  if (_current != old) {
    SDL_SetCursor(_cursor);
    _cursor = SDL_CreateSystemCursor(_current);
    SDL_SetCursor(_cursor);
  }
};

void Mouse::MouseIsSelecting()
{
  this->_mouseSelecting = true;
}

void Mouse::FreezeAutomaticSelecting(bool isFrozen, SDL_SystemCursor cursor)
{
  _current = cursor;
  _isFrozen = isFrozen;
}

void Mouse::ShowMouse(bool show) {
  SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}


/// <summary>
/// checks if the mouse is collising with a rect
/// </summary>
/// <param name="rect"></param>
/// <returns>true if the mouse is inside the rect
/// otherwise returns false</returns>
bool Mouse::IsMouseColliding(SDL_Rect rect)
{
  bool IsX = rect.x <= this->GetPos().x && (rect.x + rect.w >= this->GetPos().x);
  bool IsY = rect.y <= this->GetPos().y && (rect.y + rect.h >= this->GetPos().y);

  return IsY && IsX;
};



