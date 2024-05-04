#include "Slider.hpp"

#include <iostream>

#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "Utils.hpp"

Slider::Slider(SDL_Rect rect, int minSliderPos, int maxSliderPos, SDL_Color color, int height)
  :_rect(rect), _min(minSliderPos), _max(maxSliderPos), _color(color), _height(height)
{
  _oldPos.x = rect.x, _oldPos.y = rect.y;
};

/// <summary>
/// updates the slider rect using the mouse
/// displays the path of the slider and the slider itselfs
/// </summary>
void Slider::Update()
{
  MoveRectByMouse();
  utils::Clamp(_rect.x, _max - _rect.w, _min);
  CreateSliderPath();

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->DisplayRect(&_rect, _color);//print the block that u move
};

/// <summary>
/// creates and displays onto the renderer the slider path
/// </summary>
void Slider::CreateSliderPath()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Rect rect;

  rect.x = _min;
  rect.y = _rect.y + _rect.h / 2 - _height / 2;
  rect.w = _max - _min;
  rect.h = _height;

  SDL_Color color{ 230, 230, 230, 255 };

  window->DisplayRect(&rect, color);
};

/// <summary>
/// moves the rect using the mouse
/// </summary>
void Slider::MoveRectByMouse()
{
  Mouse* mouse = Mouse::GetMouseInstance();

  if (mouse->IsMouseColliding(_rect)) {
    mouse->MouseIsSelecting();
    if (mouse->GetPressed() == MouseButtons::mbl)
      _rect.x += mouse->GetPos().x - _oldPos.x;;
  }

  _oldPos = mouse->GetPos();
};

/// <summary>
/// returns the value of the slider
/// </summary>
/// <returns>pso of the slider</returns>
int Slider::GetValue()
{
  float width = (_max - _min - _rect.w)
    / 128.0f; // gets the amout of pixels you have to move so it will register 
  int x = _rect.x - _min; // your pos relitave to the start point
  return int(x / width); // diving and finding your value
};

/// <summary>
/// returns the rect of the slider
/// </summary>
/// <returns></returns>
SDL_Rect Slider::GetRect() {
  return _rect;
}

