#include "BasePlayer.hpp"

#include "Keyboard.hpp"
#include <vector>
#include <iostream>

BasePlayer::BasePlayer(std::vector<GIF*> gifs, bool _collisionEnabled)
  :BasePlayer::Entity((GIF*)nullptr, *gifs[0]->GetSrcRect(), *gifs[0]->GetDstRect()),
  _gifs(gifs), _currentType(GifTypes::idle), _canJump(false), _isJumping(false)
{
}

BasePlayer::~BasePlayer()
{
  for (GIF* gif: _gifs)
    delete gif;
  _gifs.clear();

}

/// <summary>
/// renders the current gif state,
/// checks if the player can jump,
/// checks for keboard input in order to move the player
/// and then it updates the players velocity
/// </summary>
void BasePlayer::Update(std::vector<Entity*> vec)
{
  this->UpdateCurrentGif();
  this->CheckJump(vec);
  this->GetInput();
  this->UpdateVelocity(vec);
}

/// <summary>
/// returns the pointer to the speed variable
/// </summary>
/// <returns></returns>
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

  else
    _speed.x = 0; //if the user isnt moving the player
}

/// <summary>
/// checks what state the gif is currenly in and updates that state
/// then it updates the gif position in the world
/// then it dispalays the gif
/// </summary>
void BasePlayer::UpdateCurrentGif()
{
  GIF* currentGif = _gifs[(int)_currentType];

  currentGif->SetDstRect(_dst);
  currentGif->Update();
  currentGif->RenderGIF(_isRight);
}

/// <summary>
/// updates the player velocity including moving the player
/// and checks if the player cannot move
/// if he connot move it resets his velocity
/// </summary>
/// <param name="vec"></param>
void BasePlayer::UpdateVelocity(std::vector<Entity*> vec)
{
  //moving in the x axis
  if (!this->MoveTo(vec, (int8_t)_speed.x, 0, true))
    _speed.x = 0; // if u cant move then remove the speed

   //moving in the y axis
   if (!this->MoveTo(vec, 0, (int8_t)_speed.y, true))
     _speed.y = 0; // if u cant move then remove the speeds
}

/// <summary>
/// checks wether or not the player can jump
/// by check if there is a block right underneath him
/// and it also applies gravity 
/// </summary>
/// <param name="vec"></param>
void BasePlayer::CheckJump(std::vector<Entity*> vec)
{
  //checking is player can still jump
  if (_isJumping && _speed.y <= MAX_JUMP) {
    _isJumping = false;
    _speed.y = MAX_JUMP;
  }

  SDL_Rect checkUnder{ _dst.x, _dst.y + _dst.h , _dst.w, 1 };
  SDL_Rect checkAbove{ _dst.x, _dst.y - 1, _dst.w, 1 };

  for (Entity* entity : vec) {
    if (entity->IsColliding(checkAbove)) {
      _isJumping = false;
      _speed.y += GRAVITY;
    }

    if (entity->IsColliding(checkUnder)) {
      _canJump = true;
      return;
    }
  }

  //applying gravity(no need to apply gravity if there a block underneath)
  if (_speed.y < MAX_GRAVITY)
    _speed.y += GRAVITY;
}
