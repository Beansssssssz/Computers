#pragma once

#include <iostream>
#include <vector>
#include <winsqlite/winsqlite3.h>

#pragma comment(lib, "winsqlite3.lib")

struct GameData {
  int money;
  uint64_t items;
  int MaxLevel;
};

struct UserData {
  std::string email;
  std::string username;
  std::string password;
  GameData* gameData = nullptr;;
};

class Server
{
public:
  static Server* GetServerInstance();
  ~Server();

  int InsertData(UserData data);
  std::vector<UserData> GetUserData();
  GameData GetGameData(int PM);
  bool DoesUserExist(UserData data);
  bool DoesUsernameExist(std::string username);
private:
  static Server* _serverPtr;
  Server();

  int CreateTables();
  int DeleteTablesData();
  int GetLastPrimaryKey();

  sqlite3* _db;
};

