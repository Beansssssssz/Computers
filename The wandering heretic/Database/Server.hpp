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
  GameData* gameData = nullptr;
};

struct LevelTimes {
  uint32_t level1_time;
  uint32_t level2_time;
  uint32_t level3_time;
  uint32_t level4_time;
  uint32_t level5_time;
};

class Server
{
public:
  static Server* GetServerInstance();
  ~Server();

  int InsertData(UserData data);
  int UpdateUserData(UserData data);

  std::vector<UserData> GetUserData();
  GameData GetGameData(int PM);
  GameData GetGameData(UserData data);

  bool DoesUserExist(UserData data);
  bool DoesUsernameExist(std::string username);

  void DisplayAllUsers();
  int GetLastPrimaryKey();

  UserData GetLastUserData();

private:
  static Server* _serverPtr;
  Server();

  int CreateTables();
  int DeleteTablesData();

  sqlite3* _db; //the database handler
  UserData _lastUserData; //the last data inputed
};

