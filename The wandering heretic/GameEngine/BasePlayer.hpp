#pragma once
#include "Entity.hpp"

#include <vector>

enum class GifTypes
{
  idle,
  attacking,
  death
};

class BasePlayer : public Entity
{
public:
  BasePlayer(std::vector<GIF*> gifs, bool _collisionEnabled = true);
  virtual ~BasePlayer();

  void Update(std::vector<Entity*> vec);

  Vector2f* GetSpeed();
private:
  void UpdateCurrentGif();
  void UpdateVelocity(std::vector<Entity*> vec);
  void CheckJump(std::vector<Entity*> vec);

  void GetInput();

protected:
  std::vector<GIF*> _gifs; //the number of gifs
  GifTypes _currentType; //the current gif of the player

  bool _canJump; //true if the player can jump
  bool _isJumping; //true if the player is currenly jump

  Vector2f _speed; //the current speed of the player

private:
  constexpr static int MAX_SPEED = 10;
  constexpr static int MAX_JUMP = -10;
  constexpr static float MAX_GRAVITY = 10.0f;

  constexpr static float JUMP = -5.0f;
  constexpr static float GRAVITY = 0.3f;
};
