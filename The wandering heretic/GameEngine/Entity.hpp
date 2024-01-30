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
  ~Entity();

  virtual void Update();
  void MoveTo(std::vector<Entity*> vec, int8_t offsetX, int8_t offsetY);

  GIF* GetGIF();
  void SetGIF(GIF* gif);

  bool GetIsRight();
  void SetIsRight(bool isRight);

protected:
  GIF* _gif; //the currently displayed gif
  bool _isRight; //a var that dipicts if the Entity if facing right(defualt)

private:
  bool _collisionEnabled; //a var that dipicits of the Entity is allowed to collide
};
