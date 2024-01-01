#include "LevelEditor.hpp"

#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "JsonParser.hpp"
#include "Utils.hpp"

#define ROUND(x, multiple) (((x) + (multiple) / 2) / (multiple) * (multiple))

LevelEditor::LevelEditor(json* data)
  :_currentBtn(NULL), _mousePressed(false), _exampleBtns(NULL),
  _tab(NULL), _movingBlock(false), _sideButtons(NULL),
  _settingBtn(NULL), _saveBtn(NULL), _resetBtn(NULL)
{
  if (data != NULL)//if it is null then vector is empty
    for (json element : *data)
      _btnVec.push_back(jsonParser::FromJsonToButton(element));

  CreateTabAndButtons();
  CreateSideButtons();
};

LevelEditor::~LevelEditor()
{
  _btnVec.clear();
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

int LevelEditor::Update()
{
  UpdateButtons();
  AddButtons();
  DisplayGrids();
  UpdateTab();
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

  for (Button* btn : _btnVec)
  {
    btn->Update();
    window->Render((Square*)btn);

    //not working fix later
    //if (mouse->IsMouseColliding(*btn->GetDstRect()))
    //  if(_currentBtn == NULL)
    //    _currentBtn = btn;
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
/// updates all the none main function buttons
/// </summary>
/// <returns></returns>
bool LevelEditor::UpdateSideButtons()
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
    return true;
  }

  return false;
}

/// <summary>
/// places the current btn at its location
/// </summary>
/// <returns>true if can be placed otherwise false</returns>
void LevelEditor::PlaceCurrentButton()
{
  for (Button* btn : _btnVec)
  {
    SDL_Rect current = *_currentBtn->GetDstRect(),
      temp = *btn->GetDstRect();
    if (utils::CmpRects(current, temp)) {
      //delete _currentBtn;
      //_currentBtn = NULL;
      return;
    }
  }
  _btnVec.push_back(_currentBtn);
}

/// <summary>
/// Creates the Tab and its example buttons
/// </summary>
void LevelEditor::CreateTabAndButtons()
{
  int x = 1600;
  int w = 1920 - 1600, h = 1080;
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
  json data;
  int i = 0;
  for (Button* btn : _btnVec)
  {
    std::string name = "Square" + std::to_string(i);
    data[name.c_str()] = jsonParser::CreateJsonFromData(*btn->GetDstRect(),
      *btn->GetSrcRect(), btn->GetPath());
    i++;
  }

  if (jsonParser::WriteToFile("C:/Users/ariel hay/Downloads/temp.json", data) != 0)
    std::cout << stderr << std::endl;
}
