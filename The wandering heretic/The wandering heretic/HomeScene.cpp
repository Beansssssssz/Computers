#include "HomeScene.hpp"

#include <iostream>
#include <SDL_thread.h>

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "Utils.hpp"

HomeScene::HomeScene()
  :_buttons(NULL), _bg(NULL), _aboutTex(NULL), _aboutExit(NULL),
  _current(HomeButtons::Play), _mousePr(false), _aboutOpen(false)
{
  //creating the background image for the current sence
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/backround_pic.png");

  SDL_Rect rect;
  rect.x = 0; rect.y = 0;
  RenderWindow::GetWidthHeight(rect.w, rect.h);
  _bg = new Square(tex, rect, rect);

  //creating key array so that you could know when a button is down and up
  _keyPressed = (bool*)calloc(4, sizeof(bool));//there are only 4 action: Confirm, Up and Down
                                               //and Esc(only for about)

  _buttons = (Button**)malloc(sizeof(Button*) * BUTTON_ARR_SIZE);
  if (_buttons == NULL)
    perror(NULL);
  _arrows = (Square**)malloc(sizeof(Button*) * BUTTON_ARR_SIZE * 2);//there are 2 arrows for each button
  if (_buttons == NULL)
    perror(NULL);

  CreateButtons();
  CreateArrows();
  CreateAboutWindow();
};

HomeScene::~HomeScene()
{
  for (int i = 0; i < BUTTON_ARR_SIZE; i++)
  {
    SDL_DestroyTexture(_buttons[i]->GetTexture());
    delete _buttons[i];
  }

  free(_buttons);
  free(_keyPressed);
};

/// <summary>
/// updates the home scene
/// the return value is the current action,the action is play:0,quit:3 or none:-1
/// </summary>
/// <returns>return the current action if no action is happing
/// then -1 is returned</returns>
int HomeScene::Update()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  //render background
  window->Render(_bg);

  if (!_aboutOpen) 
    UpdateButtons();
  else {
    AboutWindowUpdate();
    return -1;//no need to go on other iterations 
  }

  HandleInput();
  return CheckButtons();
}

/// <summary>
/// Updates and renders the Buttons and the Arrows
/// </summary>
void HomeScene::UpdateButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  ButtonResized(); //nees to applay the resizing before rending

  _mousePr = false;//reseting value
  //Buttons Update and render
  for (int i = 0; i < BUTTON_ARR_SIZE; i++)
  {
    _buttons[i]->Update();
    window->Render((Square*)_buttons[i]);
    if (_buttons[i]->GetIsSelected())
      _mousePr = true;
  }

  //render arrows
  for (int i = 0; i < BUTTON_ARR_SIZE * 2; i++)
    window->Render(_arrows[i]);

};

/// <summary>
/// updates and renders the about window
/// </summary>
void HomeScene::AboutWindowUpdate()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  window->Render(_aboutTex);
  window->Render(_aboutExit);
  _aboutExit->Update();

  if (_aboutExit->GetIsPressed())
    _aboutOpen = false;

  //check input
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Uint8* keyArr = keyboard->GetKeyArray();

  if (keyArr[SDL_SCANCODE_ESCAPE])
    _keyPressed[3] = true;

  else if (_keyPressed[3]) {//3 is esc
    _keyPressed[3] = false;
    _aboutOpen = false;
  }
};

/// <summary>
/// handles anything input related
/// </summary>
void HomeScene::HandleInput()
{
  if (_mousePr)//basicly means if the mouse is selecting dont do nothing
    return;
  _buttons[(int)_current]->SetIsSelected(false);
  _buttons[(int)_current]->SetIsPressed(false);

  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Uint8* keyArr = keyboard->GetKeyArray();
  int val = 0;

  if (keyArr[SDL_SCANCODE_E] || keyArr[SDL_SCANCODE_SPACE] || keyArr[SDL_SCANCODE_RETURN])
    _keyPressed[0] = true;

  else if (_keyPressed[0]) { //0 is confirm
    _buttons[(int)_current]->SetIsPressed(true);
    _keyPressed[0] = false;
  }

  if (keyArr[SDL_SCANCODE_W] || keyArr[SDL_SCANCODE_UP])
    _keyPressed[1] = true;

  else if (_keyPressed[1]) { //1 is up
    val = -1;
    _keyPressed[1] = false;
  }

  if (keyArr[SDL_SCANCODE_S] || keyArr[SDL_SCANCODE_DOWN])
    _keyPressed[2] = true;

  else if (_keyPressed[2]) { //2 is down
    val = 1;
    _keyPressed[2] = false;
  }

  val += (int)_current;
  utils::Clamp(val, 3, 0);

  _current = (HomeButtons)val;
  _buttons[(int)_current]->SetIsSelected(true);
};

/// <summary>
/// resizes the current selected Button so that you would know that it was selected
/// </summary>
void HomeScene::ButtonResized()
{
  int speed = -1;
  if (_isIncrease)
    speed *= -1;

  for (int i = 0; i < BUTTON_ARR_SIZE; i++) 
    if (_buttons[i]->GetIsSelected())
    {
      //left arrow
      SDL_Rect* rect = _arrows[i]->GetDstRect();
      rect->w += speed;
      rect->h += speed;
      rect->x -= speed;

      //right arrow
      rect = _arrows[i + 4]->GetDstRect();
      rect->w += speed;
      rect->h += speed;

      if (rect->w > MAX_SIZE || rect->h < MIN_SIZ)
        _isIncrease = !_isIncrease;
    }
    else
    {
      //left arrow
      SDL_Rect* rect = _arrows[i]->GetDstRect();
      rect->w = ARROWWIDTH;
      rect->h = ARROWHEIGHT;
      rect->x = _buttons[i]->GetDstRect()->x - ARROWWIDTH - MARGINX;
      
      //right arrow
      rect = _arrows[i + 4]->GetDstRect();
      rect->w = ARROWWIDTH;
      rect->h = ARROWHEIGHT;
    }
};

/// <summary>
/// checks which button is pressed then does the appropriate action
/// exmple 1: play returns 0(its value)
/// exmple 2: Help:returns -1 and opens the about window
/// </summary>
/// <returns>returns an int the enum class HomeButtons(only play or quit)
///  if no button is pressed return -1</returns>
int HomeScene::CheckButtons() {
  if (_buttons[(int)HomeButtons::Play]->GetIsPressed())
    return (int)HomeButtons::Play;

  if (_buttons[(int)HomeButtons::Quit]->GetIsPressed())
    return (int)HomeButtons::Quit;

  if (_buttons[(int)HomeButtons::Help]->GetIsPressed())
    if (!_aboutOpen) 
      _aboutOpen = true;

  if (_buttons[(int)HomeButtons::Settings]->GetIsPressed())
    return (int)HomeButtons::Settings;

  return -1;
}

/// <summary>
/// creates the buttons
/// </summary>
void HomeScene::CreateButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/HomeButtons.png");

  int w = 370, h = 91, Ystart, Xstart;

  //puts the buttons in the middle of the screen
  window->GetWidthHeight(Xstart, Ystart);
  Xstart = Xstart / 2 - w / 2;
  Ystart = Ystart / 2 - (h * 5) - MARGINY;

  SDL_Rect src = utils::InitRects(w, h), dst = utils::InitRects(w, h, Xstart, Ystart);

  window->GetWidthHeight(dst.x, dst.y);
  dst.x = dst.x / 2 - w / 2;
  dst.y = dst.y / 2 - (h * 5) - MARGINY; //looked the best for me like this

  for (int i = 0; i < BUTTON_ARR_SIZE; i++) {
    dst.y += h + MARGINY;
    src.y = h * i;
    _buttons[i] = new Button(tex, src, dst);
  }

  //56+7 is the size of an arrow and the empty space
};

/// <summary>
/// Creates the arrows
/// </summary>
void HomeScene::CreateArrows()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/Arrows.png");

  //create the left arrows
  int Xstart = _buttons[0]->GetDstRect()->x - ARROWWIDTH - MARGINX,
  Ystart = _buttons[0]->GetDstRect()->y + ARROWHEIGHT / 2 + 8;//the 8 is there because of a problem with the

  SDL_Rect src = utils::InitRects(ARROWWIDTH, ARROWHEIGHT),
    dst = utils::InitRects(ARROWWIDTH, ARROWHEIGHT, Xstart, Ystart);

  int diff = _buttons[0]->GetDstRect()->h + MARGINY;
  for (int i = 0; i < BUTTON_ARR_SIZE; i++) {
    _arrows[i] = new Square(tex, src, dst);
    dst.y += diff;
  }

  //create the right arrows

  src.y += src.h;//switching to the left arrow
  dst.x = _buttons[0]->GetDstRect()->x + _buttons[0]->GetDstRect()->w + MARGINX;
  dst.y = Ystart;

  for (int i = 0; i < BUTTON_ARR_SIZE; i++) {
    _arrows[i + 4] = new Square(tex, src, dst);
    dst.y += diff;
  }
}

/// <summary>
/// Creates the about window and its Exit button
/// </summary>
void HomeScene::CreateAboutWindow()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  int w, h, ScreenW, ScreenH;
  window->GetWidthHeight(ScreenW, ScreenH);

  char* path = const_cast<char*>("Assets/GUI/AboutText.png");
  w = 940;//width of picture
  h = 830;// height of picture

  int Xstart = ScreenW / 2 - w / 2,
      Ystart = ScreenH / 2 - h / 2;

  SDL_Rect src{ 0,0,w,h },
  dst{ Xstart, Ystart, w,h };

  _aboutTex = new Square(path, src, dst);

  //Create the Exit Button:
  path = const_cast<char*>("Assets/GUI/Xbtn.png");
  w = 25;
  h = 25;

  Xstart = dst.x + dst.w - w * 2 - MARGIN_EXIT;
  Ystart = dst.y + h + MARGIN_EXIT;
  src = SDL_Rect{ 0,0,w,h },
  dst = SDL_Rect{ Xstart, Ystart, w,h };

  _aboutExit = new Button(path, src, dst);
}
