#include "LevelEditor.hpp"

#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "JsonParser.hpp"

#define ROUND(x, multiple) (((x) + (multiple) / 2) / (multiple) * (multiple))

LevelEditor::LevelEditor(json* data)
  :_currentBtn(NULL), _mousePressed(false), _exampleBtns(NULL),
  _tab(NULL), _movingBlock(false)
{
  if (data == NULL)//if it is null then vector is empty
    return;

  for (json element : *data)
    _btnVec.push_back(jsonParser::FromJsonToButton(element));

  CreateTabAndButtons();
};

LevelEditor::~LevelEditor()
{
  SaveToFile();
  _btnVec.clear();
  delete _tab;
  delete[] _exampleBtns;
}

int LevelEditor::Update()
{
  Mouse* mouse = Mouse::GetMouseInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  int w = 32, h = 32;
  Vector2i pos = mouse->GetPos();

  int offsetX = 0;
  int offsetY = 0;

  //rounding

  pos.x = ROUND(pos.x, 32);
  pos.y = ROUND(pos.y, 32);

  for (Button* btn : _btnVec)
  {
    btn->Update();
    window->Render((Square*)btn);

    if (mouse->IsMouseColliding(*btn->GetDstRect())) {
      _currentBtn = btn;
    }
  }

  if (mouse->GetPressed() == MouseButtons::mbl && !_mousePressed) {
    _mousePressed = true;
    SDL_Rect dst = {pos.x, pos.y, h, w },
      src = { 0, 0, w, h };

    _currentBtn = new Button("Assets/ground_grass1.png", src, dst);
    window->Render((Square*)_currentBtn);
  }

  else if (mouse->GetPressed() == MouseButtons::mbl)
  {
    _currentBtn->SetDstRect({ pos.x, pos.y, h, w });
    window->Render((Square*)_currentBtn);
  }

  else if (_mousePressed)
  {
    _btnVec.push_back(_currentBtn);
    _mousePressed = false;
  }
  

  DisplayGrids();
  return 0;
}

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

/// <summary>
/// updates the buttons
/// and moves them if needed
/// </summary>
void LevelEditor::UpdateButtons()
{
  Mouse* mouse = Mouse::GetMouseInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  int w = 32, h = 32;
  Vector2i pos = mouse->GetPos();

  int offsetX = 0;
  int offsetY = 0;

  for (Button* btn : _btnVec)
  {
    btn->Update();
    window->Render((Square*)btn);

    if (mouse->IsMouseColliding(*btn->GetDstRect())) {
      _currentBtn = btn;
    }
  }
};

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
};

/// <summary>
/// 
/// </summary>
void LevelEditor::CreateTabAndButtons()
{
  int x = 1600;
  int w = 1920, h = 1080;
  SDL_Rect rect{ x, 0, w, h };
  SDL_Color color{ 255, 255, 255, 10 };
  _tab = new PopUpWindow(NULL, rect, color, true);

  _exampleBtns = new Button*[BUTTONS_COUNT];

  const char* dirPath = "Assets/Blocks/image_";
  SDL_Rect dst{ x, 0, w, h },
    src{ x, 0, w, h };

  for (char i = 0; i < BUTTONS_COUNT; i++)
  {
    std::string fullPath = dirPath + std::to_string(i) + ".png";
    std::cout << fullPath << '\n';

  }
};
