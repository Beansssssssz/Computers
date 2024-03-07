#include "Enemy.hpp"

Enemy::Enemy(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect)
  :Entity(tex, srcrect, dstrect), foundPlayer(false)
{
}

Enemy::Enemy(std::string path, SDL_Rect srcrect, SDL_Rect dstrect)
  : Entity(path, srcrect, dstrect), foundPlayer(false)
{
}

Enemy::Enemy(GIF** gif, SDL_Rect srcrect, SDL_Rect dstrect)
 :Entity(gif[0], srcrect, dstrect), foundPlayer(false)
{
}


void Enemy::Update(std::vector<Entity*> vec, BasePlayer player)
{
  Entity::Update();

  //move to right or left
  UpdateMovment(vec, player);
}
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
