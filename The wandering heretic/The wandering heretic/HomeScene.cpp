#include "HomeScene.hpp"

#include "RenderWindow.hpp"

HomeScene::HomeScene()
  :_btnExit(NULL), _btnStart(NULL), _btnSettings(NULL),
  _bg(NULL)
{
  //creating the background image for the current sence
  RenderWindow* window = RenderWindow::GetRenderWindow();
  SDL_Texture* tex = window->LoadTexture("Assets/backround_pic.png");

  SDL_Rect rect;
  rect.x = 0; rect.y = 0;
  _bg = new Square(tex, rect, rect);

  //creating the different buttons
  SDL_Rect dstRect, srcRect;
  _btnExit = new Button(NULL, rect, rect);
};

HomeScene::~HomeScene()
{
  delete _btnExit, _btnStart, _btnSettings,
    _bg;
};

void HomeScene::Update()
{
  RenderWindow* window = RenderWindow::GetRenderWindow();

  //rernder background
  window->Render(_bg);
};
