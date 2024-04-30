#include "GamePlayer.hpp"

GamePlayer::GamePlayer(std::vector<GIF*> gifs)
  :BasePlayer(gifs)
{
}

void GamePlayer::Update(std::vector<Entity*> vec)
{
  BasePlayer::Update(vec);
}
