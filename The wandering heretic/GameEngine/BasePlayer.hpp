#pragma once
#include "Entity.hpp"

#include <vector>

#define GifTypesCount 1 // all the gif types that there are

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
  BasePlayer(GIF** gifs, bool _collisionEnabled = true);
  ~BasePlayer();

  void Update(std::vector<Entity*> vec);
  void ChangeType(GifTypes type);

  Vector2f* GetSpeed();

private:
  void GetInput();
  void UpdateVelocity(std::vector<Entity*> vec);
  void CheckJump(std::vector<Entity*> vec);

private: //private members
  GIF** _gifs;
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


