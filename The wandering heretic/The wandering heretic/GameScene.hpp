#pragma once

#include "Button.hpp"

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
  int LogUser();
  char** GetAllUsers();
  void AddUser();

  std::string _currentUser;
  Square* _bg;
};
