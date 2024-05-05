#include "GameWorld.hpp"

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "JsonParser.hpp"
#include "Utils.hpp"

GameWorld::GameWorld(json* data, std::string path)
  :_data(data), _path(path),
  _player(nullptr)
{
  _vec = jsonParser::FromJsonToVector<Entity>(*data, &_enemyVec, &_finishLine);

  /* player creating */
  SDL_Rect src{ 60, 60, 178, 216 };
  SDL_Rect dst{ 65 + 200, 65, 178 / 2 , 216 / 2 };
  GIF* gif = new GIF("Assets\\Character\\FrogIdle\\FrogIdle_", 12, src, dst, 150);
  _player = new GamePlayer({ gif });

  _finishLine = SDL_Rect{500, 500 , 100, 100};
}

GameWorld::~GameWorld()
{
  for (Entity* entity: _vec)
    delete entity;

  for (Enemy* enemy : _enemyVec)
    delete enemy;

  _vec.clear();
  _enemyVec.clear();

  delete _player;
}

/// <summary>
/// updates the game world entities,
/// offsets the if needed
/// and checks whether or not to open settings
/// </summary>
/// <returns>returns none or settings</returns>
GameReturnValues GameWorld::Update()
{
  UpdateWorldOffset();
  UpdateWorldEntities();
  if (TouchedFinishLine()) {
    PlayCompletedLevel();
    return GameReturnValues::Home;
  }
  return KeyboardUpdater();
}

/// <summary>
/// updates the world using an offest saved by the player speed
/// </summary>
void GameWorld::UpdateWorldOffset()
{
  Vector2f* speed = _player->GetSpeed();
  SDL_Rect* dst = _player->GetDstRect();

  //Create offset first
  int offsetX = 0, offsetY = 0;

  int w = 0, h = 0;
  RenderWindow::GetWidthHeight(w, h);
  constexpr int startEndX = 200;
  constexpr int startEndY = 200;

  //check is the player is too far up
  //if(dst->y < startEndY)
  //  offsetY = (int)speed->y;

  //check is the player is too far down
  if (dst->y + dst->h > h - startEndY) 
    offsetY = (int)speed->y;
  
  //check is the player is too far left
  if (dst->x < startEndX) 
     offsetX = (int)speed->x;

  //check is the player is too far right
  if (dst->x + dst->w > w - startEndX) 
    offsetX = (int)speed->x;
  
  //updates vector
  this->OffestAllVector(offsetX, offsetY, dst);
}

/// <summary>
/// updates all dst rect of the entities in the vector by the offset x and y
/// also updates the dst ptr if isnt null
/// </summary>
/// <param name="offsetX"></param>
/// <param name="offsetY"></param>
/// <param name="dst"></param>
void GameWorld::OffestAllVector(int offsetX, int offsetY, SDL_Rect* dst)
{
  if (offsetX == 0 && offsetY == 0)
    return;

  SDL_Rect* rect = nullptr;

  /* entities */
  for (Entity* entity : _vec)
  {
    rect = entity->GetDstRect();
    rect->x -= offsetX;
    rect->y -= offsetY;
  }

  /* enemies */
  for (Enemy* enemy : _enemyVec) {
    rect = enemy->GetDstRect();
    rect->x -= offsetX;
    rect->y -= offsetY;
  }

  /* finish line */
  _finishLine.x -= offsetX;
  _finishLine.y -= offsetY;

  if (dst == nullptr)
    return;

  dst->x -= offsetX;
  dst->y -= offsetY;
}

/// <summary>
/// updates all the world entities
/// </summary>
void GameWorld::UpdateWorldEntities()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  _player->Update(_vec);

  for (Entity* entity : _vec)
  {
    entity->Update();
    window->Render((Square*)entity);
  }

  for (Enemy* enemy : _enemyVec)
    enemy->Update(_vec, (BasePlayer*)_player);
}

/// <summary>
/// updates all the world entities
/// </summary>
GameReturnValues GameWorld::KeyboardUpdater()
{
  Keyboard* key = Keyboard::GetKeyboardInstance();

  Uint8* keyarr = key->GetKeyArray();

  if (keyarr[SDL_SCANCODE_ESCAPE])
    return GameReturnValues::Settings;

  return GameReturnValues::None;
}

bool GameWorld::TouchedFinishLine()
{
  if(_player->IsColliding(_finishLine))
    return true;
  return false;
}

void GameWorld::PlayCompletedLevel()
{
  //play sound cue for finishing level
  //play animation for finishng level
}
