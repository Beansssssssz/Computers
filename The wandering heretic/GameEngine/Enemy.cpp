#include "Enemy.hpp"
#include <iostream>


Enemy::Enemy(std::vector<GIF*> gifs, SDL_Rect srcrect, SDL_Rect dstrect)
  :Entity((GIF*)nullptr, srcrect, dstrect), _gifs(gifs),
  _resetNextFrame(false), foundPlayer(false),
  _currentType(GifTypes::idle), _lastAttackTime(0),
  _startAttackY(0), _startAttackX(0)
{
}

Enemy::~Enemy()
{
  for (GIF* gif : _gifs)
    delete gif;

  Entity::~Entity();
}

/// <summary>
/// renders the enemy and makes him serach the for the player
/// if foudn it will try to go to him
/// otherwise he will go left until he hit a wall
/// then he goes right until he its a wall
/// </summary>
/// <param name="vec"></param>
/// <param name="player"></param>
void Enemy::Update(std::vector<Entity*>& vec, BasePlayer* player)
{
  UpdateCurrentGif();

  //move to right or left
  UpdateMovment(vec, player);
  AttackPlayer(player);
}

/// <summary>
/// updates and renders the current gif
/// </summary>
void Enemy::UpdateCurrentGif()
{
  GIF* currentGif = _gifs[(int)_currentType];

  currentGif->SetDstRect(_dst);
  currentGif->SetSrcRect(_src);
  currentGif->Update();
  currentGif->RenderGIF(_isRight);
}

/// <summary>
/// updates where the enemy needs to move to
/// using the world and the player
/// </summary>
/// <param name="vec"></param>
/// <param name="player"></param>
void Enemy::UpdateMovment(std::vector<Entity*>& vec, BasePlayer* player)
{
  /* dont move the update the enemy movment during attack */
  if (_currentType == GifTypes::attacking)
    return;

  /* check if this enemy is going right or left */
  int currentSpeed = SPEED;
  if(!_isRight)
    currentSpeed *= -1;

  /* resting the value */
  foundPlayer = false;

  /* check if u can see the if yes then try to attack him */
  if (_currentType != GifTypes::attacking && SearchForPlayer(vec, player)) 
    foundPlayer = true;

  /*
  if attacking dont move otherwise
  move the enemy and check if he hit a, if enemy hits the wall then rotate
  */
  if (!MoveTo(vec, currentSpeed, 0))
    _isRight = !_isRight;

  /* apply gravity */
  MoveTo(vec, 0, GRAVITY, true);
}

/// <summary>
/// makes the enemy search for the player
/// if found it will go to him
/// </summary>
/// <param name="vec"></param>
/// <param name="player"></param>
/// <returns></returns>
bool Enemy::SearchForPlayer(std::vector<Entity*>& vec, BasePlayer* player)
{
  SDL_Rect* playerDst = player->GetDstRect();

  //check if the player end enemy are close enough
  if (abs(playerDst->x - this->_dst.x) > ATTACK_SWING_WIDTH)
    return false;
  
  //check if the enemy is looking at the player
  if (_isRight != this->_dst.x < playerDst->x)
    return false;

  //check if the the enemy y and player diffrance is too big
  if (abs(playerDst->y - this->_dst.y) > MAX_Y_DIFFRANCE)
    return false;

  return true;
}

/// <summary>
/// attacks the player if he is close enough
/// also alters the enemy dst and src rect
/// to fit the newly dimensions
/// </summary>
/// <param name="player"></param>
void Enemy::AttackPlayer(BasePlayer* player)
{
  if (_resetNextFrame) {
    GIF* currentGif = _gifs[(int)GifTypes::idle];
    int currentTexLoc = currentGif->GetCurrentTexCount();
    SDL_Texture* currentTex = currentGif->operator[](currentTexLoc);

    int w, h;
    SDL_QueryTexture(currentTex, NULL, NULL, &w, &h);

    _src.w = w;
    _src.h = h;

    /* since enemy png is too small so i doubled it in size */
    _dst.w = w * 2;
    _dst.h = h * 2;

    /* resting the x, y pos*/
    _dst.x = _startAttackX;
    _dst.y = _startAttackY;

    _currentType = GifTypes::idle;
    _lastAttackTime = SDL_GetTicks();
    _resetNextFrame = false;
  }

  /* if he is currently attacking then alter the dst and src rects */
  if (_currentType == GifTypes::attacking) {
    ReshapeGif();
    return; /* no nned to check the if enemy needs to attack if he currently attacking*/
  }

  /* check player distance from enemy and if the enemy didnt find 
     the player then switch to attack and if the cooldown ended*/
  uint32_t currentTime = SDL_GetTicks();
  if (foundPlayer && currentTime - _lastAttackTime > ATTACK_COOLDOWN_TIMER) {
    _currentType = GifTypes::attacking;

    _startAttackY = _dst.y;
    _startAttackX = _dst.x;
  }
}

/// <summary>
/// every texture has a different width and heights so i dynamicly reshape them
/// </summary>
void Enemy::ReshapeGif()
{
  GIF* currentGif = _gifs[(int)_currentType];
  int currentTexLoc = currentGif->GetCurrentTexCount();
  SDL_Rect* dst = currentGif->GetDstRect(), * src = currentGif->GetSrcRect();
  
  SDL_Texture* currentTex = currentGif->operator[](currentTexLoc);
  int w, h;
  SDL_QueryTexture(currentTex, NULL, NULL, &w, &h);

  if (_isRight) { /* if the enemy is looking right */
    _dst.y -= h * 2 - dst->h;
  }

  else { /* if the enemy is looking left*/
    _dst.y -= h * 2 - dst->h;
    _dst.x -= w * 2 - _dst.w;
  } 

  _src.w = w;
  _src.h = h;

  /* since enemy png is too small so i doubled it in size */
  _dst.w = w * 2;
  _dst.h = h * 2;

  if (currentTexLoc == currentGif->GetTextureCount() - 1)
    _resetNextFrame = true;
}

