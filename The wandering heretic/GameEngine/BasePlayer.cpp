#include "BasePlayer.hpp"

BasePlayer::BasePlayer(GIF** gifs, SDL_Rect srcrect, SDL_Rect dstrect, bool _collisionEnabled)
  :BasePlayer::Entity(gifs[0], srcrect, dstrect), _gifs(gifs)
{

}

BasePlayer::~BasePlayer()
{
  _gif[]
  delete[] _gifs;
}

void BasePlayer::Update()
{
  Entity::Update();

}

void BasePlayer::GetInput()
{
}
