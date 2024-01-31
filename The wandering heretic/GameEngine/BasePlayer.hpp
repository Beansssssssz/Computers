#pragma once
#include "Entity.hpp"

#include <vector>

enum class GifTypes
{
  idle,
  walking,
  running,
  attacking,
  death,
};

class BasePlayer : public Entity
{
public:
  BasePlayer(GIF** gifs, bool _collisionEnabled = true);
  ~BasePlayer();

  void Update(std::vector<Entity*> vec);
private: //private functions
  void GetInput();
  void UpdateVelocity(std::vector<Entity*> vec);

private: //private members
  GIF** _gifs;

  Vector2f _speed;
  constexpr static int MAXSPEED = 5;
  constexpr static double GRAVITY = 0.1;
  constexpr static double FRICTION = 0.2;
};


