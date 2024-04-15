#include "Server.hpp"

#include <string>

Server::Server()
  :_db(nullptr)
{
  int rc = sqlite3_open("example.db", &_db); // Use a file name for disk-based database

  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(_db) << std::endl;
    sqlite3_close(_db);
    throw std::runtime_error("failed to open database");
  }

  CreateTables();
}

Server* Server::GetServerInstance()
{
  if (_serverPtr == NULL)
    _serverPtr = new Server();
  return _serverPtr;
}

/// <summary>
/// insert the UserData into the tables
/// if the game data is a nullptr then it inserts base values
/// </summary>
/// <param name="data"></param>
/// <returns>return 0 if no errors occurred otherwise returns 1</returns>
int Server::InsertData(UserData data)
{
  char* errMsg = nullptr;
  int rc;
  int PM = this->GetLastPrimaryKey() + 1; 
  if (PM == 0) {
    return 1;
  }

  std::string UsersInsert = "INSERT INTO Users(UserMail, UserName, UserPassword) \
    VALUES ('" + data.email + "', '" + data.username + "', '" + data.password + "');";

  GameData gameData = { 0,0,1 };
  if (data.gameData != nullptr)
    gameData = *data.gameData;
  std::string currentPM = std::to_string(PM);

  std::string GameDataInsert = "Insert Into GameData(UserId, Money, Items, MaxLevel)\
    VALUES('" + currentPM + "', '" + std::to_string(gameData.money) +
    "', '" + std::to_string(gameData.items) + "', '" + std::to_string(gameData.MaxLevel) + "');";

  /* inserting a user into the Users table */
  rc = sqlite3_exec(_db, UsersInsert.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in inserting data into Users. SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  /* inserting a user game data into the GameData table */
  rc = sqlite3_exec(_db, GameDataInsert.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in inserting data into GameData. SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  return 0;
}

GameData Server::GetGameData(int PM)
{
  sqlite3_stmt* stmt;
  int rc = 0;

  std::string selectStmt = "Select * FROM GameData\
    WHERE UserId = '" + std::to_string(PM) + "';";
  rc = sqlite3_prepare_v2(_db, selectStmt.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in Selecting data. SQL error: " << sqlite3_errmsg(_db) << std::endl;
    return {};
  }

  if (sqlite3_step(stmt) == SQLITE_DONE) {
    std::cerr << "No game data with UserId of: " << PM << " was found" << std::endl;
    return {};
  }

  GameData gameData{};
  gameData.money = sqlite3_column_int(stmt, 1);
  gameData.items = (uint64_t)(sqlite3_column_int64(stmt, 2));
  gameData.MaxLevel = sqlite3_column_int(stmt, 3);

  return gameData;
}

std::vector<UserData> Server::GetUserData()
{
  std::vector<UserData> dataVec;

  int rc = 0;
  sqlite3_stmt* stmt;
  const char* sqlSelectData = "SELECT * FROM Users;";

  rc = sqlite3_prepare_v2(_db, sqlSelectData, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in Selecting data. SQL error: " << sqlite3_errmsg(_db) << std::endl;
    return {};
  }

  std::string email, username, password;
  while (sqlite3_step(stmt) != SQLITE_DONE) {
    email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

    GameData* gameData = new GameData(this->GetGameData(dataVec.size() + 1));
    dataVec.push_back(UserData{ email, username, password, gameData});
  }

  sqlite3_finalize(stmt);
  return dataVec;
}

/// <summary>
/// Creates the tables and returns 0 if no error occurred
/// otherwise returns 1 and cloes the database
/// </summary>
/// <returns></returns>
int Server::CreateTables() {
  char* errMsg = nullptr;
  int rc = 0;

  const char* createUsersTable =
    "CREATE TABLE IF NOT EXISTS Users(\
      UserId INTEGER AUTO_INCREMENT PRIMARY KEY,\
      UserMail VARCHAR(50) NOT NULL UNIQUE,\
      UserName VARCHAR(50) NOT NULL UNIQUE,\
      UserPassword VARCHAR(50) NOT NULL\
    );";

  const char* createGameDataTable =
    "CREATE TABLE IF NOT EXISTS GameData(\
    UserId INT NOT NULL,\
    Money INT NOT NULL,\
    Items INT NOT NULL,\
    MaxLevel INT NOT NULL,\
    FOREIGN KEY(UserId) REFERENCES Users(UserID)\
    );";

  const char* createShopTable =
    "CREATE TABLE IF NOT EXISTS Shop(\
      ItemID INTEGER AUTO_INCREMENT PRIMARY KEY,\
      ItemName VARCHAR(50) NOT NULL,\
      Price INT NOT NULL,\
      Purpose INT NOT NULL\
    );";

  rc = sqlite3_exec(_db, createUsersTable, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in creating Users table. SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    sqlite3_close(_db);
    return 1; // Return an error code indicating failure
  }

  rc = sqlite3_exec(_db, createGameDataTable, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in creating GameData table. SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    sqlite3_close(_db);
    return 1; // Return an error code indicating failure
  }

  rc = sqlite3_exec(_db, createShopTable, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in creating Shop table. SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    sqlite3_close(_db);
    return 1; // Return an error code indicating failure
  }

  return 0;
}

int Server::DropTablesData()
{
  const char* deleteStmtUsers = "DELETE FROM Users";
  const char* deleteStmtGameData = "DELETE FROM GameData";
  char* errMSG;
  int rc = 0;

  rc = sqlite3_exec(_db, deleteStmtUsers, nullptr, nullptr, &errMSG);
  if (rc != SQLITE_OK) {
    std::cerr << "couldnt delete Users. Sql Error:" << errMSG << std::endl;

    return 1;
  }

  rc = sqlite3_exec(_db, deleteStmtGameData, nullptr, nullptr, &errMSG);
  if (rc != SQLITE_OK) {
    std::cerr << "couldnt delete Gamedata. Sql Error:" << errMSG << std::endl;

    return 1;
  }

  return 0;
}

/// <summary>
/// returns -1 if the funtion crashed.
/// if no data is in the Users table it return 0
/// otherwise retuns the last primary key
/// </summary>
/// <returns>the last primay key or the -1 otherwise the last primary key</returns>
int Server::GetLastPrimaryKey() {
  sqlite3_stmt* stmt;
  int lastPrimaryKey = 0;
  int rc = 0;

  /* Prepare the SQL statement to get the last primary key */
  const char* sql = "SELECT MAX(UserId) FROM Users;";
  rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    std::cerr << "Error in preparing to get last PM. SQL Error: " << sqlite3_errmsg(_db) << std::endl;
    sqlite3_close(_db);
    return -1;
  }

  /* Execute the statement */
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_ROW) {
    std::cerr << "Error in getting last PM. SQL Error: " << sqlite3_errmsg(_db) << std::endl;
    sqlite3_finalize(stmt);
    sqlite3_close(_db);
    return -1;
  }

  lastPrimaryKey = sqlite3_column_int(stmt, 0);
  sqlite3_finalize(stmt);

  return lastPrimaryKey;
}



