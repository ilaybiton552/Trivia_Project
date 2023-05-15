#include "SqliteDatabase.h"

/// <summary>
/// the function opens database
/// </summary>
/// <returns>if the database has opened successfully</returns>
bool SqliteDatabase::open()
{
	string dbFileName = "Trivia_DataBase.sqlite";
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &m_database); // open the database
	if (res != SQLITE_OK) // if error has occured
	{
		m_database = nullptr;
		cout << "Failed to open DataBase" << endl;
		return false;
	}

	if (file_exist != 0) // if the database doesn't exist
	{
		sqlQuery("CREATE TABLE IF NOT EXISTS USERS (USERNAME TEXT PRIMARY KEY, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);");
	}

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
	string query = "SELECT * FROM USERS WHERE (USERNAME IS \"" + username + "\");"; // the query with username to check
	string userInfo = "";

	sqlQuery(query.c_str(), getUserInfo, &userInfo);
	cout << userInfo << endl;
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
	string query = "SELECT * FROM USERS WHERE (USERNAME IS \"" + username + "\" AND PASSWORD IS \"" + password + "\"); "; // the query with username and password to check
	string userInfo = "";

	sqlQuery(query.c_str(), getUserInfo, &userInfo); // the query that return user info

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
	string query = "INSERT INTO USERS VALUES (\"" + username + "\", \"" + password + "\", \"" + email + "\");";
	return sqlQuery(query.c_str());
}

/// <summary>
/// the function does the sql query
/// </summary>
/// <param name="sqlStatement">the sql statement</param>
/// <param name="callback">the callback function</param>
/// <param name="callbackArgument">the callback argument</param>
/// <returns>if the query done without errors</returns>
bool SqliteDatabase::sqlQuery(const char* sqlStatement, int(*callback)(void*, int, char**, char**), void* callbackArgument)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(this->m_database, sqlStatement, callback, callbackArgument, errMessage); // does the query
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
	string info;

	for (int i = 0; i < argc; i++)
	{
		info += argv[i];
	}
	*(static_cast<string*>(data)) = info;

	return 0;
}

