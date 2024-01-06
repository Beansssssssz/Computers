#include "GameScene.hpp"

#include "RenderWindow.hpp"
#include "JsonParser.hpp"

#include <iostream>
#include <vector>


GameScene::GameScene()
  :_bg(NULL), _edit(NULL)
{
  json data = jsonParser::ReadFromFile("Assets/Levels/temp.json");
  _edit = new LevelEditor(&data);
};

GameScene::~GameScene()
{
  delete _bg;
  delete _edit;
};

/// <summary>
/// TODO
/// </summary>
/// <returns></returns>
int GameScene::Update()
{
  return _edit->Update();
};

void GameScene::InputUser()
{
  //create a white rect
  //if text.size() <= 0 then display in a gray-ish color the text
  //of what to input exmaple:
  // example@gmail.com
  // Enter your username
  // Enter your password
  //then when enter is pressed go into the next one
  //when inputing then make the gray text dissapear so u will know where u r
  //maybe add a small gray text flashing
}

int GameScene::LogUser()
{
  const int bufferSize = 20; // Adjust the size according to your needs
  char user[bufferSize];

  std::cout << "Please enter your username: ";
  std::cin.getline(user, bufferSize);

  //search if username is valid username:


  return 0;
}

char** GameScene::GetAllUsers()
{
  
  return nullptr;
}

/// <summary>
/// adds a user and a password
/// </summary>
void GameScene::AddUser()
{
  const int bufferSize = 20; // Adjust the size according to your needs
  char user[bufferSize];

  std::cout << "max user input is 20 characters\n";
  std::cout << "Please enter your username: ";
  std::cin.getline(user, bufferSize);
  std::cout << "\ndo u want to confirm user: " << user << " as your name(Y/N): ";

  char confirm[1];
  std::cin.getline(confirm, 1);//only get first character
  while (toupper(confirm[0]) != 'Y' || toupper(confirm[0]) != 'N')
  {
    std::cout << "\nPlease Input again: ";
    std::cin.getline(confirm, 1);
    if (toupper(confirm[0]) == 'N') {
      std::cout << "Please enter your username: ";
      std::cin.getline(user, bufferSize);
      std::cout << "\ndo u want to confirm user: " << user << " as your name(Y/N): ";
    }
  }
};
