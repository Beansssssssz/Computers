#include "GameScene.hpp"

#include "RenderWindow.hpp"
#include "JsonParser.hpp"

#include <iostream>
#include <vector>
#include <Keyboard.hpp>


GameScene::GameScene()
  :_bg(NULL), _edit(NULL), _isAdmin(false), _logUser(false)
{
  _inText = new InputText*[2];
  _inText[0] = new InputText("Enter your username", { 1920 / 2, 1080 / 2 });
  _inText[1] = new InputText("Enter your password", { 1920 / 2 - 20, 1080 / 2 - 50});
  json data = jsonParser::ReadFromFile("Assets/Levels/temp.json");
  _edit = new LevelEditor(&data);
};

GameScene::~GameScene()
{
  delete _bg;
  delete _edit;
  delete[] _inText;
};

/// <summary>
/// TODO
/// </summary>
/// <returns></returns>
int GameScene::Update()
{
  if (!_isAdmin) {
    LogUser();
    return 0;
  }
  if (_inText[0]->GetText() != "ariel")
    return 1;
  return _edit->Update();
};

void GameScene::LogUser() {
  Mouse* mouse = Mouse::GetMouseInstance();

  if (!_logUser && !mouse->IsMouseColliding(_inText[1]->GetRect())
    && mouse->GetPressed() == MouseButtons::mbl)
    _isAdmin = true;
  if (!mouse->IsMouseColliding(_inText[1]->GetRect()) && mouse->GetPressed() == MouseButtons::mbl)
    _logUser = false;
  
  _inText[0]->Update(_logUser);
  _inText[1]->Update(!_logUser);
}
