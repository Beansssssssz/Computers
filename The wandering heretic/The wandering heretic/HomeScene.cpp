#include "HomeScene.hpp"

#include <iostream>

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "Utils.hpp"


HomeScene::HomeScene()
  :_buttons(NULL), _bg(NULL), _current(HomeButton::Play)
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

  _buttons = (Button**)malloc(sizeof(Button*) * BUTTON_ARR_SIZE);
  if (_buttons == NULL)
    perror(NULL);

  CreateButtons();
};

HomeScene::~HomeScene()
{
  for (int i = 0; i < BUTTON_ARR_SIZE; i++)
    delete* _buttons;

  free(_buttons);
  free(_keyPressed);
};

void HomeScene::Update()
{
  RenderWindow* window = RenderWindow::GetRenderWindow();

  //rernder background
  window->Render(_bg);

  //Buttons Update and render
  for (int i = 0; i < BUTTON_ARR_SIZE; i++)
  {
    _buttons[i]->Update();
    window->Render((Square*)_buttons[i]);
  }
  if (_buttons[2]->GetIsPressed())
  {
    perror(NULL);
  }

  HandleInput();
  //DisplayText();
}

void HomeScene::HandleInput()
{
  int val = 0;

  Keyboard* keyboard = Keyboard::GetKeyboard();
  Uint8* keyArr = keyboard->GetKeyArray();

  if (keyArr[SDL_SCANCODE_E] || keyArr[SDL_SCANCODE_SPACE] || keyArr[SDL_SCANCODE_KP_ENTER])
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

  else if (_keyPressed[2]) {
    val = 1;
    _keyPressed[2] = false;
  }

  val += (int)_current;
  utils::Clamp(val, 3, 0);

  _current = (HomeButton)val;
};

void HomeScene::CreateButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindow();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/HomeButtons.png");

  int w = 500, h = 92;

  SDL_Rect src = utils::InitRects(w, h), dst = utils::InitRects(w, h);
  //window->GetWidthHeight(dst.x, dst.y);
  /*dst.x = dst.x / 2 - w / 2;
  dst.y /= 4;*/

  for (int i = 0; i < BUTTON_ARR_SIZE; i++) {
    dst.x = 0;
    switch (i)
    {
    case 0:
      dst.x = 1000;
      break;
    case 1:
      dst.y = 0;
      break;
    case 2:
      dst.y = 92;
      break;
    case 3:
      dst.y = 92 + 92 + 100;
      break;
    }
    //src.y += i * dst.h;
    _buttons[i] = new Button(tex, src, dst);
  }
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
