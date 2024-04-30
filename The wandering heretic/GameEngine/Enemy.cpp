#include "Enemy.hpp"


Enemy::Enemy(std::vector<GIF*> gifs, SDL_Rect srcrect, SDL_Rect dstrect)
 :Entity((GIF*)nullptr, srcrect, dstrect), _gifs(gifs),
  foundPlayer(false), _currentType(GifTypes::idle)
{
}

void Enemy::Update(std::vector<Entity*> vec, BasePlayer player)
{
  UpdateCurrentGif();

  //move to right or left
  UpdateMovment(vec, player);
}

/// <summary>
/// updates and renders the current gif
/// </summary>
void Enemy::UpdateCurrentGif()
{
  GIF* currentGif = _gifs[(int)_currentType];

  currentGif->SetDstRect(_dst);
  currentGif->Update();
  currentGif->RenderGIF(_isRight);
}

/// <summary>
/// updtes where the enemy needs to move to
/// </summary>
/// <param name="vec"></param>
/// <param name="player"></param>
void Enemy::UpdateMovment(std::vector<Entity*> vec, BasePlayer player)
{
  //check if this enemy is going right or left
  int currentSpeed = _isRight ? SPEED : SPEED * -1;

  //check if u can see the player:
  if (SearchForPlayer(vec, player)) {
    foundPlayer = true;

    currentSpeed = player.GetDstRect()->x > this->_dst.x ? SPEED : -SPEED;
    MoveTo(vec, currentSpeed, 0);
    return;
  }

  //move the enemy and check if he hit a wall
  //if enemy hits the wall then rotate
  bool canMove = MoveTo(vec, currentSpeed, 0);

  if (!canMove)
    _isRight = !_isRight;
}

/// <summary>
/// makes the enemy search for the player
/// if found it will go to him
/// </summary>
/// <param name="vec"></param>
/// <param name="player"></param>
/// <returns></returns>
bool Enemy::SearchForPlayer(std::vector<Entity*> vec, BasePlayer player)
{
  SDL_Rect* playerDst = GetDstRect();

  //check if the player end enemy are close enough
  if (playerDst->x - this->_dst.x > DISTANCE_MAX) {
    foundPlayer = false;
    return false;
  }

  //check if the enemy is looking at the player
  if ((_isRight != this->_dst.x < playerDst->x) && foundPlayer)
    return false;

  //check if the the enemy y and player diffrance is too big
  if (playerDst->y - this->_dst.y > MAX_Y_DIFFRANCE)
    return false;

  return true;
}
