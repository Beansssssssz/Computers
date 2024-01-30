#include "BasePlayer.hpp"

#include "Keyboard.hpp"
#include <vector>
#include <iostream>

BasePlayer::BasePlayer(GIF** gifs, bool _collisionEnabled)
  :BasePlayer::Entity(gifs[0], gifs[0]->GetDstRect(), gifs[0]->GetSrcRect()),
  _gifs(gifs)
{
}

BasePlayer::~BasePlayer()
{
  _gif = nullptr;//incase of UB
  delete[] _gifs;
}

/// <summary>
/// TODO
/// </summary>
void BasePlayer::Update(std::vector<Entity*> vec)
{
  Entity::Update();
  this->GetInput();
  this->UpdateVelocity();
}

void BasePlayer::GetInput()
{
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Uint8* keyArr = keyboard->GetKeyArray();

  if (keyArr[SDL_SCANCODE_W] || keyArr[SDL_SCANCODE_UP])
    _speed.y = -MAXSPEED;

  if (keyArr[SDL_SCANCODE_D] || keyArr[SDL_SCANCODE_RIGHT])
    _speed.x = MAXSPEED;

  if (keyArr[SDL_SCANCODE_A] || keyArr[SDL_SCANCODE_LEFT])
    _speed.x = -MAXSPEED;
}


void BasePlayer::UpdateVelocity()
{
  std::vector<Entity*> vec;

  //moving the player
  if (_speed.x != 0 || _speed.y != 0)
  {

    int8_t x = (int8_t)_speed.x;
    int8_t y = (int8_t)_speed.y;
    if (_speed.x < 0)
      std::cout << ((int)x) << '\n';
    this->MoveTo(vec, x, y);
  }

  //slowing the player
  if (_speed.x != 0)
    _speed.x += _speed.x > 0 ? -1 : 1 * FRICTION;

  //applaying gravity to the player
 /* if (_speed.y > MAXSPEED)
    _speed.y += _speed.y + GRAVITY;*/
}
