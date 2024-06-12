#include "GameWorld.hpp"

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "JsonParser.hpp"
#include "Utils.hpp"
#include "WindowText.hpp"
#include <Audio.hpp>

GameWorld::GameWorld(json* data, std::string path)
  :_data(data), _path(path), _finishLine(nullptr),
  _player(nullptr), _startTime(SDL_GetTicks()), _highestYBlock(0)
  ,_showDeadWindow(false)
{
  _finishLine = new Square((SDL_Texture*)NULL, { 0,0,0,0 }, { 0,0,0,0 });
  _vec = jsonParser::FromJsonToVector<Entity>(*data, &_enemyVec, _finishLine);

  /* player creating */
  SDL_Rect src{ 60, 60, 178, 216 };
  SDL_Rect dst{ 65 + 200, 65, 178 / 2 , 216 / 2 };
  GIF* gif = new GIF("Assets\\Character\\FrogIdle\\FrogIdle_", 12, src, dst, 150);
  _player = new GamePlayer({ gif });
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
  delete _finishLine;
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
  PlayerFell();
  PlayerWasHit();

  if (_showDeadWindow != 0) 
    return DisplayDeadWindow();

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
  rect = _finishLine->GetDstRect();
  rect->x -= offsetX;
  rect->y -= offsetY;

  /* lowest block y position */
  _highestYBlock -= offsetY;

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

  window->Render(_finishLine);

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

/// <summary>
/// checks if the player has touched the finish line
/// </summary>
/// <returns></returns>
bool GameWorld::TouchedFinishLine()
{
  if(_player->IsColliding(*_finishLine->GetDstRect()))
    return true;

  return false;
}

/// <summary>
/// plays the completed Level sound cue
/// plays an animation singaling u finished the level
/// unlockes the next level
/// </summary>
void GameWorld::PlayCompletedLevel()
{
  if (!_showDeadWindow) {
    UserData newData = _player->GetUserData();
    newData.gameData->MaxLevel += 1;
    _player->SetUserData(newData);
  }

  //play sound cue for finishing level
  Audio* audio = Audio::GetAudioInstance();
  audio->SetMusic("Assets/Sounds/FinishLevel.mp3", 1, 1, true);
}

/// <summary>
/// checks if the player fell more than 1 block down then the most down block
/// </summary>
void GameWorld::PlayerFell()
{
  if (_highestYBlock == 0)
  {
    for (Entity* entity : _vec) {
      int currentEntityY = entity->GetDstRect()->y;
      _highestYBlock = (currentEntityY > _highestYBlock) ? currentEntityY : _highestYBlock;
    }
  }

  if (_player->GetDstRect()->y + 64 >= _highestYBlock && _showDeadWindow == 0)
    _showDeadWindow = SDL_GetTicks();
}

/// <summary>
/// checks if the player was hit by an enemy while the enemy is in an attack state
/// </summary>
void GameWorld::PlayerWasHit()
{
  for (Enemy* enemy : _enemyVec) {
    if (enemy->AttackWorked(_player))
    {
      _showDeadWindow = SDL_GetTicks();
      return;
    }
  }
}

/// <summary>
/// displays the dead window for a set amount of time then returns
/// </summary>
/// <returns></returns>
GameReturnValues GameWorld::DisplayDeadWindow()
{
  /* if timer finished */
  Uint32 currentTime = SDL_GetTicks();
  if(currentTime >= GAME_OVER_TIMER + _showDeadWindow)
    return GameReturnValues::Home;

  /* displaying the overlay rect */
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Rect windowRect{ 0, 0, 0, 0 };
  RenderWindow::GetWidthHeight(windowRect.w, windowRect.h);
  window->DisplayRect(&windowRect, GAME_OVER_RECT_COLOR);

  /* dispalying the text */
  Vector2i textPos{ windowRect.w / 2, windowRect.h / 2 };
  WindowText::DisplayStaticText("GAME OVER", textPos, GAME_OVER_TEXT_COLOR, GAME_OVER_TEXT_SIZE, true);
  return GameReturnValues::None;
}
