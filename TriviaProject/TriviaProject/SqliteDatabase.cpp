#include "SqliteDatabase.h"

/// <summary>
/// the function opens database
/// </summary>
/// <returns>if the database has opened successfully</returns>
bool SqliteDatabase::open()
{
	sqlite3* db;
	string dbFileName = "Trivia_DataBase.sqlite";
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db); // open the database
	if (res != SQLITE_OK) // if error has occured
	{
		db = nullptr;
		cout << "Failed to open DataBase" << endl;
		return false;
	}

	if (file_exist != 0) // if the database doesn't exist
	{
		sqlQuery(db, "CREATE TABLE IF NOT EXISTS Users(USERNAME TEXT PRIMARY KEY, PASSWORD TEXT, EMAIL TEXT);");
	}

	this->m_database = db;
	return true;
}

/// <summary>
/// the funciton closes the database
/// </summary>
/// <returns>if the database has closed successfully</returns>
bool SqliteDatabase::close()
{
	sqlite3_close(this->m_database);
	this->m_database = nullptr;
	return true;
}

/// <summary>
/// the function checks if user exists according to his username
/// </summary>
/// <param name="username">the username to check if exists</param>
/// <returns>if the user exists</returns>
int SqliteDatabase::doesUserExist(const string username)
{
	string query = "SELECT * FROM Users WHERE (USERNAME IS \"" + username + "\");"; // the query with username to check
	string userInfo = "";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->m_database, query.c_str(), getUserInfo, &userInfo, &errMessage); // the query that return user info
	if (res != SQLITE_OK)
	{
		std::cout << "Error has occurred: " << errMessage << std::endl;
	}
	
	return (userInfo != ""); // if the database returned userinfo - user exists, else - the user doesn't exist
}

/// <summary>
/// the function checks if the password matches the username
/// </summary>
/// <param name="username">the username to check</param>
/// <param name="password">the password to check</param>
/// <returns>if the password matches the username</returns>
int SqliteDatabase::doesPasswordMatch(const string username, const string password)
{
	string query = "SELECT * FROM Users WHERE (USERNAME IS \"" + username + "\" AND PASSWORD IS \"" + password + "\"); "; // the query with username and password to check
	string userInfo = "";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->m_database, query.c_str(), getUserInfo, &userInfo, &errMessage); // the query that return user info
	if (res != SQLITE_OK)
	{
		std::cout << "Error has occurred: " << errMessage << std::endl;
	}

	return (userInfo != ""); // if the database returned userinfo - the password match, else - the password doesn't match
}

/// <summary>
/// the function adds user to the database
/// </summary>
/// <param name="username">the username</param>
/// <param name="password">the password</param>
/// <param name="email"></param>
/// <returns></returns>
int SqliteDatabase::addNewUser(const string username, const string password, const string email)
{
	string query = "INSERT INTO Users VALUES (\"" + username + "\", \"" + password + "\", \"" + email + "\");";
	return sqlQuery(this->m_database, query.c_str());
}

/// <summary>
/// the function does a sql query
/// </summary>
/// <param name="db">the database</param>
/// <param name="sqlStatement">the query that we want to be done</param>
/// <returns>if the query comleted successfully</returns>
bool SqliteDatabase::sqlQuery(sqlite3* db, const char* sqlStatement)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage); // does the query
	if (res != SQLITE_OK) // if an error has occured
	{
		cout << "Error has occurred: " << errMessage << endl;
		return false;
	}

	return true;
}

/// <summary>
/// the function convets the sql data to string with user information
/// </summary>

int SqliteDatabase::getUserInfo(void* data, int argc, char** argv, char** azColName)
{
	string info = *(static_cast<string*>(data));

	for (int i = 0; i < argc; i++)
	{
		info += argv[i];
	}

	return 0;
}

