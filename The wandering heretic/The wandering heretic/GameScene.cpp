#include "GameScene.hpp"

#include "RenderWindow.hpp"
#include "JsonParser.hpp"

#include <iostream>
#include <Keyboard.hpp>

GameScene::GameScene()
  :_bg(NULL), _edit(NULL), _isAdmin(false), _logUser(false)
{
  int w, h;
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->GetWidthHeight(w, h);
  _bg = new Square("Assets/backround_pic.png", { 0,0,w,h }, { 0,0,w,h });

  CreateInputTextAreas();

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
  //if (!_isAdmin) {
  //  LogUser();
  //  return 0;
  //}
  return _edit->Update();
};

/// <summary>
/// Logs the user
/// </summary>
void GameScene::LogUser() {
  Mouse* mouse = Mouse::GetMouseInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  //renders the backround
  window->Render(_bg);

  //creates the text rect from,
  SDL_Rect textRect = _inText[1]->GetRvalueRect();

  if (!_logUser && !mouse->IsMouseColliding(textRect)
    && mouse->GetPressed() == MouseButtons::mbl)
    _isAdmin = true;
  if (!mouse->IsMouseColliding(textRect) && mouse->GetPressed() == MouseButtons::mbl)
    _logUser = false;
  
  _inText[0]->Update(_logUser);
  _inText[1]->Update(!_logUser);
}

void GameScene::CreateInputTextAreas()
{
  _inText = new InputText * [2];

  int w, h;
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->GetWidthHeight(w, h);
  _inText[0] = new InputText("Enter your username", { w / 2, h / 2 });
  _inText[1] = new InputText("Enter your password", { w / 2 , h / 2});

  const double margin = 1.0/5.0;//the margin between the the inputText sqaures
  const double margineCaculated = (1.0 - margin) / 2;

  const int InpuTextW = _inText[0]->GetSquareWidth(); //they have the same width
  const int InpuTextH = _inText[0]->GetSquareHeight(); // and height

  Vector2i* inputTextRect;
  //username rect Fixing
  inputTextRect = _inText[0]->GetPos();

  inputTextRect->x = w / 2 - InpuTextW / 2;
  inputTextRect->y = margineCaculated * h - InpuTextH / 2;

  //password rect fixing
  inputTextRect = _inText[1]->GetPos();
  inputTextRect->x = w / 2 - InpuTextW / 2;
  inputTextRect->y = (margineCaculated + margin) * h - InpuTextH / 2;
}
