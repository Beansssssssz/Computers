#include "Enemy.hpp"

Enemy::Enemy(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect)
  :Entity(tex, srcrect, dstrect)
{
}

Enemy::Enemy(std::string path, SDL_Rect srcrect, SDL_Rect dstrect)
  : Entity(path, srcrect, dstrect)
{
}


void Enemy::Update(std::vector<Entity*> vec)
{
  Entity::Update();

  //move to right or left
  SearchForPlayer(vec);

}

void Enemy::SearchForPlayer(std::vector<Entity*> vec)
{
  int currentSpeed = GetIsRight() == true ? SPEED : SPEED * -1;
  bool canMove = MoveTo(vec, currentSpeed, 0);//the enemy only jumps when needed

  if (!canMove) 
    _isRight = !_isRight;

}
