#include "GameWorld.hpp"

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "JsonParser.hpp"

GameWorld::GameWorld(json* data, std::string path)
  :_data(data), _path(path),
  _player(nullptr), _settingsBtn(nullptr)
{
  for (json block : *data)
  {
    Square* sqr = jsonParser::FromJsonToSquare(block, false);
    Entity* entity = new Entity(sqr->GetTexture(), *sqr->GetSrcRect(), *sqr->GetDstRect());
    _vec.push_back(entity);

    delete sqr;
  }

  SDL_Rect rect{ 60, 60, 188, 260 - 42 };
  GIF* gif = new GIF("Assets\\Character\\FrogIdle\\FrogIdle_", 12, rect, rect, 180);
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
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  _player->Update(_vec);
  for (Entity* entity : _vec)
  {
    entity->Update();
    window->Render((Square*)entity);
  }
  return false;
}
