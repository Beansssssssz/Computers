#pragma once

#include "Entity.hpp"
#include "BasePlayer.hpp"


class Enemy : public Entity
{
public :
  Enemy(std::vector<GIF*> gifs, SDL_Rect srcrect, SDL_Rect dstrect);


  void Update(std::vector<Entity*> vec, BasePlayer player);
private:
  void UpdateCurrentGif();
  void UpdateMovment(std::vector<Entity*> vec, BasePlayer player);
  bool SearchForPlayer(std::vector<Entity*> vec, BasePlayer player);

  std::vector<GIF*> _gifs;
  GifTypes _currentType;
  bool foundPlayer;

  static constexpr int DISTANCE_MAX = 300;
  static constexpr int MAX_Y_DIFFRANCE = 300;
  static constexpr int SPEED = 5;
};

