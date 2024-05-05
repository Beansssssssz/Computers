#include "Enemy.hpp"


Enemy::Enemy(std::vector<GIF*> gifs, SDL_Rect srcrect, SDL_Rect dstrect)
  :Entity((GIF*)nullptr, srcrect, dstrect), _gifs(gifs),
  _originalDst(dstrect), _originalSrc(srcrect), _resetNextFrame(false),
  foundPlayer(false), _currentType(GifTypes::idle)
{
}

/// <summary>
/// renders the enemy and makes him serach the for the player
/// if foudn it will try to go to him
/// otherwise he will go left until he hit a wall
/// then he goes right until he its a wall
/// </summary>
/// <param name="vec"></param>
/// <param name="player"></param>
void Enemy::Update(std::vector<Entity*> vec, BasePlayer* player)
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
void Enemy::UpdateMovment(std::vector<Entity*> vec, BasePlayer* player)
{
  /* resting the value */
  foundPlayer = false;

  /* check if this enemy is going right or left */
  int currentSpeed = _isRight ? SPEED : SPEED * -1;

  /* check if u can see the player
    if yes then go to him */
  if (SearchForPlayer(vec, player)) {
    foundPlayer = true;

    currentSpeed = player->GetDstRect()->x > this->_dst.x ? SPEED : -SPEED;
    if (currentSpeed > 0)
      _isRight = true;
    else
      _isRight = false;
  }

  /* move the enemy and check if he hit a wall
     if enemy hits the wall then rotate */
  if (_currentType != GifTypes::attacking && !MoveTo(vec, currentSpeed, 0))
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
bool Enemy::SearchForPlayer(std::vector<Entity*> vec, BasePlayer* player)
{
  SDL_Rect* playerDst = player->GetDstRect();

  //check if the player end enemy are close enough
  if (abs(playerDst->x - this->_dst.x) > DISTANCE_MAX) 
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
    _dst.w = _originalDst.w;
    _dst.h = _originalDst.h;

    _src.w = _originalSrc.w;
    _src.h = _originalSrc.h;

    _currentType = GifTypes::idle;
  }

  /* if he is currently attacking then alter the dst and src rects */
  if (_currentType == GifTypes::attacking) {
    ReshapeGif();
  }

  /* check player distance from enemy or if the enemy didnt find 
     the player then switch to attack */
  if (foundPlayer && (player->GetDstRect()->x - this->_dst.x < LARGEST_ATTACK_WIDTH - _dst.w)) 
    _currentType = GifTypes::attacking;
}

/// <summary>
/// every texture has a different width and heights so i dynamicly reshape them
/// </summary>
void Enemy::ReshapeGif()
{
  _resetNextFrame = false;
  GIF* currentGif = _gifs[(int)_currentType];
  int currentTexLoc = currentGif->GetCurrentTexCount();
  SDL_Rect* dst = currentGif->GetDstRect(), * src = currentGif->GetSrcRect();
  
  SDL_Texture* currentTex = currentGif->operator[](currentTexLoc);
  int w, h;
  SDL_QueryTexture(currentTex, NULL, NULL, &w, &h);

  _src.w = w;
  _src.h = h;



  //_dst.x -= w - dst->w;
  //_dst.y -= h - dst->h;
      
  _dst.w = w * 2;
  _dst.h = h * 2;
   
  if (currentTexLoc == currentGif->GetTextureCount() - 1)
    _resetNextFrame = true;
}

