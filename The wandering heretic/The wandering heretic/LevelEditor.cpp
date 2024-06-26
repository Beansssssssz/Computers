#include "LevelEditor.hpp"

#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "KeyBoard.hpp"
#include "JsonParser.hpp"
#include "Utils.hpp"

//rounds out the x var to the nearest multiple of multiple
#define ROUND(x, multiple) (((x) + (multiple) / 2) / (multiple) * (multiple))

LevelEditor::LevelEditor(json* data, std::string path)
  :_currentBtn(NULL), _mousePressed(false), _exampleBtns(NULL),
  _tab(NULL), _movingBlock(false), _sideButtons(NULL),
  _settingBtn(NULL), _saveBtn(NULL), _resetBtn(NULL), _path(path)
  , _offsetY(0), _offsetX(0)
{
  _btnVec = jsonParser::FromJsonToVector<Button>(*data, nullptr, nullptr);

  CreateTabAndButtons();
  CreateSideButtons();

  _stackActions = new bool[2];
  _stackActions[0] = false;
  _stackActions[1] = false;
};

LevelEditor::~LevelEditor()
{
  _btnVec.clear();

  while (!_stack.empty()) {
    delete _stack.top(); //deletes the element
    _stack.pop(); //pops the element
  }
  delete _stackActions;

  delete _tab;
  delete[] _exampleBtns;
  if (_currentBtn != NULL)
    delete _currentBtn;

  //deleting side var
  delete _settingBtn;
  delete _saveBtn;
  delete _resetBtn;
  delete _sideButtons;
}

/// <summary>
/// updates the all the levelEditor functions as
/// needed and check for input from the user
/// </summary>
/// <returns></returns>
GameReturnValues LevelEditor::Update()
{
  UpdateButtons();
  AddButtons();
  DisplayGrids();
  UpdateTab();
  HandleInput();
  MoveVectorWorld();
  return UpdateSideButtons();
}

/// <summary>
/// Updates the vector buttons
/// and moves them if their pressed
/// </summary>
void LevelEditor::UpdateButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Mouse* mouse = Mouse::GetMouseInstance();

  _movingBlock = false;
  for (Button* btn : _btnVec)
  {
    btn->Update();
    window->Render((Square*)btn);
  }
}

/// <summary>
/// Adds The Buttons to the vector
/// </summary>
void LevelEditor::AddButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Mouse* mouse = Mouse::GetMouseInstance();
  Vector2i pos = mouse->GetPos();

  pos.y = ROUND(pos.y, GRID_HEIGHT);
  pos.x = ROUND(pos.x, GRID_WIDTH);

  if (_currentBtn != NULL) {
    if (mouse->GetPressed() == MouseButtons::mbl) {
      _currentBtn->SetDstRect(SDL_Rect{pos.x, pos.y, GRID_WIDTH, GRID_HEIGHT});
      window->Render((Square*)_currentBtn);
      _mousePressed = true;
    }

    else if(_mousePressed)
    {
      PlaceCurrentButton();
      _mousePressed = false;
      _currentBtn = NULL;
    }
    return;
  }

  for (char i = 0; i < BUTTONS_COUNT; i++)
    if (mouse->IsMouseColliding(*_exampleBtns[i]->GetDstRect())
      && mouse->GetPressed() == MouseButtons::mbl) {
      delete _currentBtn;
      _currentBtn = new Button(*_exampleBtns[i]);
    }
};

/// <summary>
/// displays the grids into the screen in order to help the
/// map editor to know where is block will be placed
/// </summary>
void LevelEditor::DisplayGrids()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  SDL_Rect rect{0, 0, 1920, 1};
  SDL_Color white{255, 255, 255, 20};
  for (int i = 0; i < (1080 + 32) / GRID_HEIGHT; i++) {
    window->DisplayRect(&rect, white);
    rect.y += GRID_HEIGHT;
  }

  rect = SDL_Rect{0, 0, 1, 1080 };
  for (int i = 0; i < 1920 / GRID_WIDTH; i++) {
    window->DisplayRect(&rect, white);
    rect.x += GRID_WIDTH;
  }
}

/// <summary>
/// updates the tab and the exmple buttons
/// </summary>
void LevelEditor::UpdateTab()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  _tab->Update();
  for (char i = 0; i < BUTTONS_COUNT; i++)
  {
    window->Render((Square*)_exampleBtns[i]);
    _exampleBtns[i]->Update();
  }
}

/// <summary>
/// Hanldes input related actions
/// </summary>
void LevelEditor::HandleInput()
{
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Uint8* keyarr = keyboard->GetKeyArray();

  if (keyarr[SDL_SCANCODE_LCTRL] && keyarr[SDL_SCANCODE_Z])
    _stackActions[0] = true;

  else if (_stackActions[0]) {
    _stackActions[0] = false;
    if (_btnVec.size() <= 0)
      return;

    _stack.push(_btnVec.back());//basically takes the last element and puts it in the stack
    _btnVec.pop_back();//pops the last element out of the vector

    return;
  }

  if (keyarr[SDL_SCANCODE_LCTRL] && keyarr[SDL_SCANCODE_Y])
    _stackActions[1] = true;

  else if (_stackActions[1]) {
    _stackActions[1] = false;

    if (_stack.size() <= 0)
      return;

    _btnVec.push_back(_stack.top());//takes the top element in the stack and puts it into vector
    _stack.pop(); // pops the top element from the stack
  }

}

/// <summary>
/// updates all the none main function buttons
/// returns true if to open up settings otherwise returns false
/// </summary>
/// <returns></returns>
GameReturnValues LevelEditor::UpdateSideButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  //save button
  window->Render((Square*)_saveBtn);
  _saveBtn->Update();
  if (_saveBtn->GetIsPressed())
    _sideButtons[0] = true;

  else if (_sideButtons[0]) {
    _sideButtons[0] = false;
    SaveToFile();
  }

  //reset buttons
  window->Render((Square*)_resetBtn);
  _resetBtn->Update();

  if (_resetBtn->GetIsPressed())
    _sideButtons[1] = true;

  else if (_sideButtons[1]) {
    _sideButtons[1] = false;
    _btnVec.clear();
  }

  //settings button
  window->Render((Square*)_settingBtn);
  _settingBtn->Update();

  if (_settingBtn->GetIsPressed())
    _sideButtons[2] = true;

  else if (_sideButtons[2]) {
    _sideButtons[2] = false;
    return GameReturnValues::Settings;
  }

  return GameReturnValues::None;
}

/// <summary>
/// offset the world vector as needed
/// is the mouse wheel has changed
/// it moves the y as the mouse wheel
/// however if there is a shift detected
/// also it moves the x
/// </summary>
void LevelEditor::MoveVectorWorld()
{
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Mouse* mouse = Mouse::GetMouseInstance();
  int offsetY = mouse->GetScrollY();

  if (offsetY == 0)
    return;

  offsetY = offsetY > 0 ? 64 : -64;

  int offsetX = 0;
  Uint8* keyArr = keyboard->GetKeyArray();
  if (keyArr[SDL_SCANCODE_LSHIFT]) {
    offsetX = offsetY;
    offsetY = 0;
  }

  _offsetX += offsetX;
  _offsetY += offsetY;

  SDL_Rect* rect = nullptr;
  for (Button* entity : _btnVec)
  {
    rect = entity->GetDstRect();
    rect->x += offsetX;
    rect->y += offsetY;
  }
}

/// <summary>
/// places the current btn at its location
/// </summary>
/// <returns>true if can be placed otherwise false</returns>
void LevelEditor::PlaceCurrentButton()
{
  for (Button* btn : _btnVec)
  {
    SDL_Rect current = *_currentBtn->GetDstRect(), temp = *btn->GetDstRect();

    if (SDL_HasIntersection(&current, &temp)) 
      return;
  }

  _btnVec.push_back(_currentBtn);
}

/// <summary>
/// Creates the Tab and its example buttons
/// </summary>
void LevelEditor::CreateTabAndButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  int w, h, x;
  window->GetWidthHeight(w, h);
  x = (int)(w * 0.85f);
  w = (int)(1920 * 0.15f);

  SDL_Rect rect{ x, 0, w, h };
  SDL_Color color{ 90, 200, 170, 255 };
  _tab = new PopUpWindow(NULL, rect, color, true);

  //create the exmple buttons:
  _exampleBtns = new Button*[BUTTONS_COUNT];

  const char* dirPath = "Assets/Blocks/image_";
  SDL_Rect dst{ x, 0, 64, 64 },
    src{ 0, 0, 64, 64 };

  //find margins
  int marginY = (rect.h - dst.h * BUTTONS_COUNT) / BUTTONS_COUNT;
  int marginX = (rect.w - dst.w * 2) / 3;

  //start the first column
  dst.y = marginY;
  dst.x += marginX;
  for (char i = 0; i < 8; i++)
  {
    std::string fullPath = dirPath + std::to_string(i) + ".png";
    _exampleBtns[i] = new Button(fullPath.c_str(), src, dst);
    dst.y += marginY + dst.h;
  };

  //start the second column
  dst.y = marginY;
  dst.x += marginX + dst.w;//counting the size of the block
  for (char i = 8; i < BUTTONS_COUNT; i++)
  {
    std::string fullPath = dirPath + std::to_string(i) + ".png";
    _exampleBtns[i] = new Button(fullPath.c_str(), src, dst);
    dst.y += marginY + dst.h;
  };
}

/// <summary>
/// Creates all the none main function buttons
/// </summary>
void LevelEditor::CreateSideButtons()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  //create settings:
  SDL_Rect dst = { 0,0,50,50 },
    src = { 0,0,50,50 };
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/GearIcon.png");
  _settingBtn = new Button(tex, src, dst);

  //create save:
  dst = { 0,1080 - 91,200,90 };
  src.w = 200; src.h = 90;
  tex = window->LoadTexture("Assets/GUI/SaveBtn.png");
  _saveBtn = new Button(tex, src, dst);

  //create resete:
  dst = { 50,0,91, 50};
  src.w = 91;
  tex = window->LoadTexture("Assets/GUI/ResetBtn.png");
  _resetBtn = new Button(tex, src, dst);

  _sideButtons = new bool[3];

  for (char i = 0; i < 3; i++)
    _sideButtons[i] = false;
}

/// <summary>
/// Saves the current buttons vector to a file in a json format
/// </summary>
void LevelEditor::SaveToFile()
{
  //change the offset back to 0,0
  SDL_Rect* rect = nullptr;
  for (Button* entity : _btnVec)
  {
    rect = entity->GetDstRect();
    rect->x -= _offsetX;
    rect->y -= _offsetY;
  }

  //write to file
  json data = jsonParser::FromVectorToJson(_btnVec);
  jsonParser::WriteToFile(_path.c_str(), &data);

  //restore the original offset
  rect = nullptr;
  for (Button* entity : _btnVec)
  {
    rect = entity->GetDstRect();
    rect->x += _offsetX;
    rect->y += _offsetY;
  }
}
