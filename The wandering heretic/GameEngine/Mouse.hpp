#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Square.hpp"
#include "Math.hpp"

enum class MouseButtons {
  none = 0,
  mbl = 1,
  mbm = 2,
  mbr = 4,
  mb4 = 8,
  mb5 = 16
};

class Mouse
{
public:
  ~Mouse();
  static Mouse* GetMouseInstance();
  Vector2i GetPos();
  MouseButtons GetPressed();

  void Update();
  void UpdatePos();

  void ChangeCursorType();
  void MouseIsSelecting();
  void FreezeAutomaticSelecting(bool isFrozen, SDL_SystemCursor cursor
    = SDL_SYSTEM_CURSOR_ARROW);

  bool IsMouseColliding(SDL_Rect rect);
private:
  static Mouse* _mousePtr;
  Mouse(Vector2i pos);

  MouseButtons bt = MouseButtons::none;
  Vector2i pos;
  SDL_Cursor* _cursor;
  SDL_SystemCursor _current;
  bool _mouseSelecting;

  bool _isFrozen;
};
