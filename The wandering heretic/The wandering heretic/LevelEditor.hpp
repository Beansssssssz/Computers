#pragma once

#include <vector>
#include <stack>
#include <nlohmann/json.hpp>

#include "Button.hpp"
#include "PopUpWindow.hpp"

using json = nlohmann::json;

#define GRID_WIDTH 64
#define GRID_HEIGHT 64

//the counter of the amount of example blocks to use
#define BUTTONS_COUNT 9

class LevelEditor 
{
public:
  LevelEditor(json* data, std::string path);
  ~LevelEditor();

  int Update();
private:
  void UpdateButtons();
  void AddButtons();
  void DisplayGrids();
  void UpdateTab();
  void HandleInput();
  bool UpdateSideButtons();
  void MoveVectorWorld();

  void PlaceCurrentButton();
  void CreateTabAndButtons();
  void CreateSideButtons();
  void SaveToFile();

  json _data;

  std::vector<Button*> _btnVec;
  Button* _currentBtn;
  bool _mousePressed;

 
  std::stack<Button*> _stack; //the stack that keeps the buttons placed
  bool* _stackActions; // the array that keeps track of what buttons are placed

  //the tab where the exmples of the Squares u can create the levels are in.
  PopUpWindow* _tab;
  Button** _exampleBtns;// the buttons that u can use in the level editor

  bool _movingBlock; /// for later when i implinaite moving a object

  //side var:

  Button* _settingBtn; // the settings button
  Button* _resetBtn; // the settings button
  Button* _saveBtn; // the settings button

  bool* _sideButtons;

  std::string _path;
};

