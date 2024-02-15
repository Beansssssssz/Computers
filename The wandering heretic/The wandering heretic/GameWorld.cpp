#include "GameWorld.hpp"

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "JsonParser.hpp"

GameWorld::GameWorld(json* data, std::string path)
  :_data(data), _path(path),
  _player(nullptr), _settingsBtn(nullptr)
{
  _vec = jsonParser::FromJsonToVector<Entity>(*data);

  SDL_Rect src{ 60, 60, 178, 260 - 42 };
  SDL_Rect dst{ 100, 500, 178 , 218 };
  GIF* gif = new GIF("Assets\\Character\\FrogIdle\\FrogIdle_", 12, src, dst, 180);
  _player = new BasePlayer(&gif);
}

GameWorld::~GameWorld()
{
  for (size_t i = 0; i < _vec.size(); i++)
    delete _vec[i];

  delete _player;
  delete _settingsBtn;
}

bool GameWorld::Update()
{

  this->UpdateWorldPos();
  this->UpdateWorldEntities();
  return false;
}

void GameWorld::UpdateWorldPos()
{
  Vector2f* speed = _player->GetSpeed();
  SDL_Rect* dst = _player->GetDstRect();

  //Create offset first
  int offsetX = 0, offsetY = 0;

  int w = 0, h = 0;
  RenderWindow::GetWidthHeight(w, h);

  constexpr char div = 16;

  //check is the player is too far up
  if(dst->y < h / div)
    offsetY = (int)speed->y;

  //check is the player is too far down
  if(dst->y >  h - h / div)
    offsetY = (int)speed->y;

  //check is the player is too far left
  if(dst->x < w / div)
    offsetX = (int)speed->x;

  //check is the player is too far right
  if (dst->x > w - w / div)
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
  if (!offsetX && !offsetY)
    return;

  SDL_Rect* rect = nullptr;
  for (Entity* entity : _vec)
  {
    rect = entity->GetDstRect();
    rect->x -= offsetX;
    rect->y -= offsetY;
  }

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
}
