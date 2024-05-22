#pragma once

#include "Entity.hpp"
#include "BasePlayer.hpp"


class Enemy : public Entity
{
public :
  Enemy(std::vector<GIF*> gifs, SDL_Rect srcrect, SDL_Rect dstrect);
  ~Enemy();

  void Update(std::vector<Entity*>& vec, BasePlayer* player);
  bool AttackWorked(BasePlayer* player);
private:
  void UpdateCurrentGif();
  void UpdateMovment(std::vector<Entity*>& vec, BasePlayer* player);
  bool SearchForPlayer(std::vector<Entity*>& vec, BasePlayer* player);
  void AttackPlayer(BasePlayer* player);
  void ReshapeGif();

  std::vector<GIF*> _gifs; //all the gif types
  GifTypes _currentType; //current gif type
  bool foundPlayer; //true if found the player
  int _originalW; //the width of the player without the sword
  uint8_t _canDamage; //when the attacking gif start dealing damage

  bool _resetNextFrame; //tells the enemy to leave the current frame and reset into the idle
  uint32_t _lastAttackTime;
  int _startAttackY;
  int _startAttackX;

  static constexpr int ATTACK_SWING_WIDTH = 120;
  static constexpr int MAX_Y_DIFFRANCE = 64;
  static constexpr int SPEED = 5;
  static constexpr int GRAVITY = 5;
  static constexpr uint32_t ATTACK_COOLDOWN_TIMER = 1200;
};

