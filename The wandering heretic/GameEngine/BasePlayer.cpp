#include "BasePlayer.hpp"

#include "Keyboard.hpp"
#include <vector>
#include <iostream>

BasePlayer::BasePlayer(GIF** gifs, bool _collisionEnabled)
  :BasePlayer::Entity(gifs[0], gifs[0]->GetSrcRect(), gifs[0]->GetDstRect()),
  _gifs(gifs), _currentType(GifTypes::idle), _canJump(true), _isJumping(false)
{
}

BasePlayer::~BasePlayer()
{
  for (size_t i = 1; i < GifTypesCount; i++)
    delete _gifs[i];
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

Vector2f* BasePlayer::GetSpeed()
{
  return &_speed;
}

/// <summary>
/// Gets and Handles all the input that the player is supposed to recive
/// </summary>
void BasePlayer::GetInput()
{
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Uint8* keyArr = keyboard->GetKeyArray();

  if ((keyArr[SDL_SCANCODE_W] || keyArr[SDL_SCANCODE_UP] || keyArr[SDL_SCANCODE_SPACE]) && (_canJump || _isJumping)) {
    _speed.y += JUMP;
    _canJump = false;
    _isJumping = true;
  }
  else
    _isJumping = false;

  if (keyArr[SDL_SCANCODE_D] || keyArr[SDL_SCANCODE_RIGHT]) {
    _speed.x = MAX_SPEED;
    _isRight = true;
  }

  else if (keyArr[SDL_SCANCODE_A] || keyArr[SDL_SCANCODE_LEFT]) {
    _speed.x = -MAX_SPEED;
    _isRight = false;
  }
}


/// <summary>
/// updates the plater velocity including moving the player
/// </summary>
/// <param name="vec"></param>
void BasePlayer::UpdateVelocity(std::vector<Entity*> vec)
{
  //moving in the x axis
   this->MoveTo(vec, (int8_t)_speed.x, 0, true);

   //moving in the y axis
   this->MoveTo(vec, 0, (int8_t)_speed.y, true);

  //resting the speed;
  _speed.x = 0;

  //applying gravity
  if (_speed.y < MAX_GRAVITY)
    _speed.y += GRAVITY;

  //checking is player can still jump
  if (_isJumping && _speed.y <= MAX_JUMP) {
    _isJumping = false;
    _speed.y = MAX_JUMP;
  }
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
