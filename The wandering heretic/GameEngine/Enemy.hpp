#pragma once
#include "Entity.hpp"


class Enemy : public Entity
{
public :
  Enemy(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect);
  Enemy(std::string path, SDL_Rect srcrect, SDL_Rect dstrect);


  void Update(std::vector<Entity*> vec);
private:
  void SearchForPlayer(std::vector<Entity*> vec);


  static constexpr int SPEED = 5;
};

