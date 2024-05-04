#pragma once

#include "Entity.hpp"
#include "BasePlayer.hpp"


class Enemy : public Entity
{
public :
  Enemy(std::vector<GIF*> gifs, SDL_Rect srcrect, SDL_Rect dstrect);

  void Update(std::vector<Entity*> vec, BasePlayer* player);
private:
  void UpdateCurrentGif();
  void UpdateMovment(std::vector<Entity*> vec, BasePlayer* player);
  bool SearchForPlayer(std::vector<Entity*> vec, BasePlayer* player);
  void AttackPlayer(BasePlayer* player);
  void ReshapeGif();

  std::vector<GIF*> _gifs;
  GifTypes _currentType;
  bool foundPlayer;

  SDL_Rect _originalSrc;
  SDL_Rect  _originalDst;
  bool _resetNextFrame;

  static constexpr int DISTANCE_MAX = 1080;
  static constexpr int MAX_Y_DIFFRANCE = 300;
  static constexpr int SPEED = 5;
  static constexpr int GRAVITY = 5;
  static constexpr int LARGEST_ATTACK_WIDTH = 140;
};

