#include "Server.hpp"

#include <string>

Server::Server()
  :_db(nullptr)
{
  int rc = sqlite3_open("Assets/DataBases/database.db", &_db); // Use a file name for disk-based database

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

Server::~Server()
{
  sqlite3_close(_db);
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
  std::string PM = std::to_string(this->GetLastPrimaryKey() + 1);
  if (PM == "0")
    return 1;
  
  std::string UsersInsert = "INSERT INTO Users(UserId, UserMail, UserName, UserPassword) \
    VALUES ('" + PM + "', '" + data.email + "', '" + data.username + "', '" + data.password + "');";

  GameData gameData = { 0,0,1 };
  if (data.gameData != nullptr)
    gameData = *data.gameData;

  std::string GameDataInsert = "Insert Into GameData(UserId, Money, Items, MaxLevel)\
    VALUES('" + PM + "', '" + std::to_string(gameData.money) +
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

/// <summary>
/// returns the gameData that has the same ID
/// if no gameData exists returns an empty data
/// </summary>
/// <param name="PM"></param>
/// <returns></returns>
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

/// <summary>
/// returns the GameData using the password and ethier email or username
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
GameData Server::GetGameData(UserData data)
{
  sqlite3_stmt* stmt;
  int rc = 0, PM = -1;

  std::string selectStmt = "SELECT * FROM Users WHERE ";

  if (data.email != "") //if there is email
    selectStmt += "UserMail = '" + data.email + "' AND ";
  else //if there is username
    selectStmt += "UserName = '" + data.username + "' AND ";

  selectStmt += "UserPassword = '" + data.password + "';";

  rc = sqlite3_prepare_v2(_db, selectStmt.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in Selecting data. SQL error: " << sqlite3_errmsg(_db) << std::endl;
    return {};
  }

  if (sqlite3_step(stmt) == SQLITE_DONE) {
    std::cerr << "No user data in server was found the is matching user data " << std::endl;
    return {};
  }

  PM = sqlite3_column_int(stmt, 0);
  GameData gameData = this->GetGameData(PM);

  return gameData;
}

/// <summary>
/// checks if the users exist in the database
/// returns true if user exist otherwise returns false
/// </summary>
/// <param name="data">gameData isnt used, email or username is must
/// and so is password</param>
/// <returns></returns>
bool Server::DoesUserExist(UserData data)
{
  sqlite3_stmt* stmt;
  int rc = 0;

  std::string FindUserStatment =  "SELECT * FROM Users\
    WHERE ";

  if(!data.email.empty() && !data.username.empty())
    FindUserStatment += "UserMail = '" + data.email + "' UserName = '" + data.username + "' ";
  else if (!data.email.empty()) //if the user inputed username
    FindUserStatment += "UserName = '" + data.email + "' ";
  else //if the user inputed email
    FindUserStatment += "UserName = '" + data.username + "' ";
  
  FindUserStatment += "AND UserPassword = '" + data.password + "';";

  rc = sqlite3_prepare_v2(_db, FindUserStatment.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in Selecting data. SQL error: " << sqlite3_errmsg(_db) << std::endl;
    return false;
  }

  if (sqlite3_step(stmt) == SQLITE_DONE) 
    return false;

  return true;
}

/// <summary>
/// returns true if the username exist in the database
/// </summary>
/// <param name="username"></param>
/// <returns></returns>
bool Server::DoesUsernameExist(std::string username) {
  sqlite3_stmt* stmt;
  int rc = 0;

  std::string FindUserStatment = "SELECT * FROM Users\
    WHERE UserName = '" + username + "';";

  rc = sqlite3_prepare_v2(_db, FindUserStatment.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed in Selecting data. SQL error: " << sqlite3_errmsg(_db) << std::endl;
    return false;
  }

  if (sqlite3_step(stmt) == SQLITE_DONE)
    return false;

  return true;
}

/// <summary>
/// returns all the users as a vector
/// </summary>
/// <returns></returns>
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

    GameData* gameData = new GameData(this->GetGameData((int)dataVec.size() + 1));
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
      UserId INTEGER AUTO INCREMENT PRIMARY KEY,\
      UserMail VARCHAR(50) NOT NULL,\
      UserName VARCHAR(50) NOT NULL,\
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

/// <summary>
/// deletes all the data from the tables
/// </summary>
/// <returns></returns>
int Server::DeleteTablesData()
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

void Server::DisplayAllUsers() {
  std::vector<UserData> vec = this->GetUserData();
  int PM = 1;

  for (UserData data : vec) {
    std::cout << "user id: " << PM << ", " <<
      "email: " << data.email << ", " <<
      "username: " << data.username << ", " <<
      "password: " << data.password << ", " <<
      std::endl;
  }
}
