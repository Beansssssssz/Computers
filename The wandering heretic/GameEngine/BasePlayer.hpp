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
  BasePlayer(GIF** gifs, bool _collisionEnabled = true);
  ~BasePlayer();

  void Update(std::vector<Entity*> vec);
  void ChangeType(GifTypes type);
private: //private functions
  void GetInput();
  void UpdateVelocity(std::vector<Entity*> vec);

private: //private members
  GIF** _gifs;
  GifTypes _currentType;

  Vector2f _speed;
  constexpr static int MAX_SPEED = 10;
  constexpr static float GRAVITY = 0.3f;
  constexpr static float MAX_GRAVITY = 10.0f;
};


