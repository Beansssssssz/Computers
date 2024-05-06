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

  std::vector<GIF*> _gifs; //all the gif types
  GifTypes _currentType; //current gif type
  bool foundPlayer; //true if found the player

  //because of usage of muiltple gifs there is muiltple dst and src rect
  //so this is the original of the idle animation
  SDL_Rect _originalSrc;
  SDL_Rect  _originalDst;
  bool _resetNextFrame; //tells the enemy to leave the current frame and reset into the idle

  static constexpr int DISTANCE_MAX = 1080;
  static constexpr int MAX_Y_DIFFRANCE = 300;
  static constexpr int SPEED = 5;
  static constexpr int GRAVITY = 5;
  static constexpr int LARGEST_ATTACK_WIDTH = 140;
};

