#pragma once
#include "Square.hpp"
#include "GIF.hpp" 

#include <vector>

class Entity :public Square
{
public:
  Entity(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled = true);
  Entity(std::string path, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled = true);
  Entity(GIF* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled = true);
  virtual ~Entity();

  virtual void Update();
  bool MoveTo(std::vector<Entity*> vec, int8_t offsetX, int8_t offsetY, bool snap = false);
  void SnapToRect(SDL_Rect rect, int8_t offsetX, int8_t offsetY);

  GIF* GetGIF();
  void SetGIF(GIF* gif);

  bool GetIsRight();
  void SetIsRight(bool isRight);

protected:
  GIF* _gif; //if you wanted to use a gif instead of a single texture.
  bool _isRight; //a var that dipicts if the Entity if facing right(defualt)

private:
  bool _collisionEnabled; //a bool var, if false then when moving it ignores collision
};
