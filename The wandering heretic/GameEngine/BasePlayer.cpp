#include "BasePlayer.hpp"

#include "Keyboard.hpp"
#include <vector>
#include <iostream>

BasePlayer::BasePlayer(GIF** gifs, bool _collisionEnabled)
  :BasePlayer::Entity(gifs[0], gifs[0]->GetDstRect(), gifs[0]->GetSrcRect()),
  _gifs(gifs), _currentType(GifTypes::idle), _canJump(true)
{
}

BasePlayer::~BasePlayer()
{
  //TODO
  //delete _gifs;
}

/// <summary>
/// Updates and renders the Player class
/// </summary>
void BasePlayer::Update(std::vector<Entity*> vec)
{
  Entity::Update();

  this->CheckJump(vec);
  this->GetInput();
  this->UpdateVelocity(vec);
}

void BasePlayer::ChangeType(GifTypes type)
{
  _currentType = type;
}

/// <summary>
/// Gets and Handles all the input that the player is supposed to recive
/// </summary>
void BasePlayer::GetInput()
{
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Uint8* keyArr = keyboard->GetKeyArray();

  if ((keyArr[SDL_SCANCODE_W] || keyArr[SDL_SCANCODE_UP] || keyArr[SDL_SCANCODE_SPACE]) && _canJump) {
    _speed.y = JUMP_VEL;
    _canJump = false;
  }

  else if (keyArr[SDL_SCANCODE_S] || keyArr[SDL_SCANCODE_DOWN])
    _speed.y = -JUMP_VEL;

  if (keyArr[SDL_SCANCODE_D] || keyArr[SDL_SCANCODE_RIGHT])
    _speed.x = MAX_SPEED;

  else if (keyArr[SDL_SCANCODE_A] || keyArr[SDL_SCANCODE_LEFT])
    _speed.x = -MAX_SPEED;
}


/// <summary>
/// updates the plater velocity including moving the player
/// </summary>
/// <param name="vec"></param>
void BasePlayer::UpdateVelocity(std::vector<Entity*> vec)
{
  //moving the player
  if (_speed.x != 0) 
   this->MoveTo(vec, (int8_t)_speed.x, 0);
  
  if (_speed.y != 0) 
    while(!this->MoveTo(vec, 0, (int8_t)_speed.y))
      _speed.y += (_speed.y > 0 ? -1 : 1);
  

  //applying friction and smoothness to the player
  if (_speed.x != 0)
    _speed.x += _speed.x > 0 ? -1 : 1;

  //applying gravity
  if (_speed.y < MAX_GRAVITY)
    _speed.y += GRAVITY;
}

void BasePlayer::CheckJump(std::vector<Entity*> vec)
{
  SDL_Rect check{ _dst.x, _dst.y + _dst.h , _dst.w, 1 };
  for(Entity* entity: vec)
    if (entity->IsColliding(check)) {
      _canJump = true;
      return;
    }
}
