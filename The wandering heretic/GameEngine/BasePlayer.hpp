#pragma once
#include "Entity.hpp"

#include <vector>

enum class GifTypes
{
  idle,
  walking,
  running,
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

private: //private members
  std::vector<GIF*> _gifs;
  GifTypes _currentType;

  bool _canJump;
  bool _isJumping;

  Vector2f _speed;
  constexpr static int MAX_SPEED = 10;
  constexpr static int MAX_JUMP = -10;
  constexpr static float MAX_GRAVITY = 10.0f;

  constexpr static float JUMP = -2.0f;
  constexpr static float GRAVITY = 0.3f;
};


