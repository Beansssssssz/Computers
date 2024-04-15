#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Mouse.hpp"
#include "Utils.hpp"

Mouse::Mouse(Vector2i _pos)
  :_current(SDL_SYSTEM_CURSOR_ARROW), _isFrozen(false), _mouseSelecting(false),
  _scrollY(0) , _isScrolling(false)
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
  if (_mousePtr == nullptr)
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

/// <summary>
/// updates the pos and pressing button of the mouse
/// changes the cursor type based on if its hovering or not
/// </summary>
void Mouse::Update()
{
  bt = MouseButtons(SDL_GetMouseState(&_pos.x, &_pos.y));
  ChangeCursorType();

  _mouseSelecting = false;//setting up for the next frame

  //checking is the mouse didnt scroll
  if (!_isScrolling)
    _scrollY = 0;

  //reseting the scrolling
  _isScrolling = false;
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

/// <summary>
/// using the events tab it checks if the event is a mouse scroll wheel
/// if yes then adds the y to the var
/// </summary>
/// <param name="ev"></param>
void Mouse::SetScrollYFromEvent(SDL_Event ev) {
  if (ev.type == SDL_MOUSEWHEEL) {
    _scrollY = ev.wheel.y;
    _isScrolling = true;
  }
}

int Mouse::GetScrollY() {
  return _scrollY;
}

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



