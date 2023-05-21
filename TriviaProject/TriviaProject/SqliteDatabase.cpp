#include "SqliteDatabase.h"

/// <summary>
/// the function opens database
/// </summary>
/// <returns>if the database has opened successfully</returns>
bool SqliteDatabase::open()
{
	int file_exist = _access(DB_FILE_NAME, 0);
	int res = sqlite3_open(DB_FILE_NAME, &m_database); // open the database
	if (res != SQLITE_OK) // if error has occured
	{
		m_database = nullptr;
		cout << "Failed to open DataBase" << endl;
		return false;
	}

	if (file_exist != 0) // if the database doesn't exist
	{
		sqlQuery("CREATE TABLE IF NOT EXISTS USERS (USERNAME TEXT PRIMARY KEY, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL, ADDRESS TEXT NOT NULL, PHONE TEXT NOT NULL, BIRTH_DATE TEXT NOT NULL);");
		sqlQuery("CREATE TABLE IF NOT EXISTS STATISTICS (USERNAME TEXT NOT NULL, IS_CORRECT_ANSWER INTEGER NOT NULL, ANSWER_TIME REAL NOT NULL, GAMES INTEGER NOT NULL, FOREIGN KEY(USERNAME) REFERENCES USERS(USERNAME)); ");
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
int SqliteDatabase::addNewUser(const string username, const string password, const string email, const string address, const string phone, const string birthDate)
{
	string query = "INSERT INTO USERS VALUES (\"" + username + "\", \"" + password + "\", \"" + email + "\", \"" + address + "\", \"" + phone + "\", \"" + birthDate + "\");";
	return sqlQuery(query.c_str());
}

/// <summary>
/// Gets the average time of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>float, the username's average answer time</returns>
float SqliteDatabase::getPlayerAverageTime(const string& username)
{
	return 0.0f;
}

/// <summary>
/// Gets the number of correct answers of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the number of correct answers of the player</returns>
int SqliteDatabase::getNumOfCorrectAnswers(const string& username)
{
	return 0;
}

/// <summary>
/// Gets the number of total answers of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the number of total answers of the player</returns>
int SqliteDatabase::getNumOfTotalAnswers(const string& username)
{
	return 0;
}

/// <summary>
/// Gets the number of total games of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the number of games answers of the player</returns>
int SqliteDatabase::getNumOfTotalGames(const string& username)
{
	return 0;
}

/// <summary>
/// Gets a playre's score
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the score of the player</returns>
int SqliteDatabase::getPlayerScore(const string& username)
{
	return 0;
}

/// <summary>
/// Gets the high scores
/// </summary>
/// <returns>vector of string, vector of users with high scores</returns>
vector<string> SqliteDatabase::getHighScores()
{
	return vector<string>();
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

