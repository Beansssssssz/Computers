#include "GamePlayer.hpp"

GamePlayer::GamePlayer(std::vector<GIF*> gifs)
  :BasePlayer(gifs)
{
}

/// <summary>
/// updates the player class
/// </summary>
/// <param name="vec"></param>
void GamePlayer::Update(std::vector<Entity*> vec)
{
  BasePlayer::Update(vec);
  //CheckGifType(); i only have a single animation
}

///// <summary>
///// checks which GifState the player needed to currently be at
///// </summary>
//void GamePlayer::CheckGifType()
//{
//  _currentType = GifTypes::idle;
//}
