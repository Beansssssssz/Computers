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
  void ChangeCursorType();

  void MouseIsSelecting();
  void FreezeAutomaticSelecting(bool isFrozen, SDL_SystemCursor cursor
    = SDL_SYSTEM_CURSOR_ARROW);

  bool IsMouseColliding(SDL_Rect rect);
private:
  static Mouse* _mousePtr;
  Mouse(Vector2i pos);

  MouseButtons bt = MouseButtons::none;
  Vector2i _pos; // the pos of the cursor
  SDL_Cursor* _cursor; // the cursor
  SDL_SystemCursor _current; // current cursor
  bool _mouseSelecting; // if the mouse is currently selecting smth

  bool _isFrozen;// if mouse is frozen.
};
