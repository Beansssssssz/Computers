#include "HomeScene.hpp"

#include <iostream>

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "Utils.hpp"


HomeScene::HomeScene()
  :_btnPlay(NULL), _btnQuit(NULL), _btnSettings(NULL),
  _btnHelp(NULL) ,_bg(NULL), _current(HomeButton::Play)
{
  //creating the background image for the current sence
  RenderWindow* window = RenderWindow::GetRenderWindow();
  SDL_Texture* tex = window->LoadTexture("Assets/backround_pic.png");

  SDL_Rect rect;
  rect.x = 0; rect.y = 0;
  RenderWindow::GetWidthHeight(rect.w, rect.h);
  _bg = new Square(tex, rect, rect);

  //creating key array so that you could know when a button is down and up
  _keyPressed = (bool*)calloc(3, sizeof(bool));//there are only 3 action: Confirm, Up and Down
};

HomeScene::~HomeScene()
{
  delete _btnQuit, _btnPlay, _btnSettings,
    _btnHelp, _bg;

  free(_keyPressed);
};

void HomeScene::Update()
{
  RenderWindow* window = RenderWindow::GetRenderWindow();

  //rernder background
  window->Render(_bg);

  HandleInput();
  DisplayText();
}

void HomeScene::HandleInput()
{
  int val = 0;

  Keyboard* keyboard = Keyboard::GetKeyboard();
  Uint8* keyArr = keyboard->GetKeyArray();

  if (keyArr[SDL_SCANCODE_E] || keyArr[SDL_SCANCODE_SPACE] ||keyArr[SDL_SCANCODE_KP_ENTER])
      _keyPressed[0] = true;

  else if (_keyPressed[0]) {
    _keyPressed[0] = false;
  }

  if (keyArr[SDL_SCANCODE_W] || keyArr[SDL_SCANCODE_UP])
    _keyPressed[1] = true;

  else if (_keyPressed[1]) {
    val = -1;
    _keyPressed[1] = false;
  }

  if (keyArr[SDL_SCANCODE_S] || keyArr[SDL_SCANCODE_DOWN])
    _keyPressed[2] = true;

  else if(_keyPressed[2]){
    val = 1;
    _keyPressed[2] = false;
  }

  val += (int)_current;
  utils::Clamp(val, 3, 0);

  _current = (HomeButton)val;
};

void HomeScene::DisplayText()
{

  


  switch (_current)
  {
  case HomeButton::Play:
    std::cout << "Playyyyyyy" << std::endl;
    break;
  case HomeButton::Settings:
    std::cout << "Settingssssssssssssss" << std::endl;
    break;
  case HomeButton::Help:
    std::cout << "Helpppppppp" << std::endl;
    break;
  case HomeButton::Quit:
    std::cout << "Quitttttttttt" << std::endl;
    break;
  }
}
