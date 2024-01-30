#include "GameWorld.hpp"

#include "Keyboard.hpp"

GameWorld::GameWorld()
  :_player(nullptr), _settingsBtn(nullptr)
{
  _vec.push_back(nullptr);

  SDL_Rect rect{ 0,0,320,320 };
  GIF* gif = new GIF("Assets\\Character\\FrogIdle\\FrogIdle_", 12, rect, rect, 180);
  _player = new BasePlayer(&gif);
}

GameWorld::~GameWorld()
{
  for (size_t i = 0; i < _vec.size(); i++)
    delete _vec[0];

  delete _settingsBtn;
}

bool GameWorld::Update()
{
  _player->Update(_vec);

  return true;
}
