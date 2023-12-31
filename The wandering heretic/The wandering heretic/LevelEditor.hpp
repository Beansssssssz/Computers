#pragma once

#include <vector>
#include <nlohmann/json.hpp>

#include "Button.hpp"
#include "PopUpWindow.hpp"


using json = nlohmann::json;

#define GRID_WIDTH 32
#define GRID_HEIGHT 32

class LevelEditor 
{
public:
  LevelEditor(json* data = NULL);
  ~LevelEditor();

  int Update();
private:
  void UpdateButtons();
  void DisplayGrids();
  void CreateTabAndButtons();

  json _data;

  std::vector<Button*> _btnVec;
  Button* _currentBtn;
  bool _mousePressed;

  //the tab where the exmples of the Squares u can create the levels are in.
  PopUpWindow* _tab;
  Button** _exampleBtns;// the buttons that u can used in the level editor

  bool _movingBlock;
};

