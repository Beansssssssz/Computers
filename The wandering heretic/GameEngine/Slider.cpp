#include "Slider.hpp"

#include <iostream>

#include "RenderWindow.hpp"
#include "Mouse.hpp"


Slider::Slider(SDL_Rect rect, int pos1, int pos2, RGBA color, int height)
  :_rect(rect), _pos1(pos1), _pos2(pos2), _color(color), _height(height)
{
  _oldPos.x = rect.x, _oldPos.y = rect.y;
};

/// <summary>
/// the update function of the slider
/// </summary>
void Slider::Update()
{
  MoveRectByMouse();
  ClampDstRectX();
  CreateSliderPath();

  RenderWindow* window = RenderWindow::GetRenderWindow();
  window->DisplayRect(&_rect, _color);//print the block that u move
};

/// <summary>
/// creates and displays onto the renderer the slider path
/// </summary>
void Slider::CreateSliderPath()
{
  RenderWindow* window = RenderWindow::GetRenderWindow();
  SDL_Rect rect;

  rect.x = _pos1;
  rect.y = _rect.y + (_rect.w / 2);
  rect.w = _pos2 - _pos1;
  rect.h = _height;

  RGBA color(230, 230, 230, 255);

  window->DisplayRect(&rect, color);
};

/// <summary>
/// moves the rect using the mouse
/// </summary>
void Slider::MoveRectByMouse()
{
  Mouse* mouse = Mouse::GetMouse();

  if (mouse->IsMouseColliding(_rect)) {
    mouse->MouseIsSelecting();
    if (mouse->GetPressed() == MouseButtons::mbl)
      _rect.x += mouse->GetPos().x - _oldPos.x;;
  }

  _oldPos = mouse->GetPos();

  
};

/// <summary>
///clamps the x of the rect so that it
/// wouldnt go outbounds
/// </summary>
void Slider::ClampDstRectX()
{
  if (_rect.x > _pos2)
    _rect.x = _pos2;
  if (_rect.x < _pos1)
    _rect.x = _pos1;
};

/// <summary>
/// returns the value of the slider
/// </summary>
/// <returns>pso of the slider</returns>
int Slider::GetValue()
{
  float width = (_pos2 - _pos1) / 100; // gets the amout of pixels you have to move so it will register 
  int x = _rect.x - _pos1; // your pos relitave to the start point
  return int(x / width); // diving and finding your value
};


