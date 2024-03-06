#pragma once

#include "Entity.hpp"
#include "BasePlayer.hpp"


class Enemy : public Entity
{
public :
  Enemy(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect);
  Enemy(std::string path, SDL_Rect srcrect, SDL_Rect dstrect);


  void Update(std::vector<Entity*> vec, BasePlayer player);
private:
  void UpdateMovment(std::vector<Entity*> vec, BasePlayer player);
  bool SearchForPlayer(std::vector<Entity*> vec, BasePlayer player);


  static constexpr int DISTANCE_MAX = 300;
  static constexpr int MAX_Y_DIFFRANCE = 300;
  static constexpr int SPEED = 5;
};

