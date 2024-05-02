#include "GameScene.hpp"

#include "RenderWindow.hpp"
#include "JsonParser.hpp"
#include "Utils.hpp"

#include <iostream>
#include <Keyboard.hpp>

GameScene::GameScene()
  :_bg(nullptr), _edit(nullptr), _cn(nullptr), _world(nullptr)
{
  int w, h;
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->GetWidthHeight(w, h);
  _bg = new Square("Assets/backround_pic.png", { 0,0,w,h }, { 0,0,w,h });

  _cn = new ChooseNumber(10);
};

GameScene::~GameScene()
{
  if (_edit != nullptr) {}
    delete _edit;
  if (_world != nullptr)
    delete _world;
  if(_cn != nullptr)
    delete _cn;

  delete _bg;
};

/// <summary>
/// select the level that is going to run and the type of game
/// an editing world
/// or an player world
/// </summary>
/// <returns></returns>
GameReturnValues GameScene::Update()
{
  if (_cn != nullptr)
  {
    int num = _cn->Update();
    if (num > 0) //if u chose a level
    {
      std::string path = "Assets/Levels/Level_" + std::to_string(num) + ".json";
      json data = jsonParser::ReadFromFile(path.c_str());

      _world = new GameWorld(&data, path);
      //_edit = new LevelEditor(&data, path);

      delete _cn;
      _cn = nullptr;
    }

    else if (!_cn->GetIsOpen()) //if u closed
    {
      delete _cn;
      _cn = nullptr;

      return GameReturnValues::Home;
    }

    return GameReturnValues::None;
  }

    return _world->Update();

  //return _edit->Update();
};
