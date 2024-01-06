#pragma once

#include "Button.hpp"
#include "LevelEditor.hpp"

#include <string>

enum class Mode
{

};

class GameScene
{
public:
  GameScene();
  ~GameScene();

  int Update();
private:
  void InputUser();
  int LogUser();
  char** GetAllUsers();
  void AddUser();

  std::string _currentUser;
  Square* _bg;

  LevelEditor* _edit;//the level editor
};
