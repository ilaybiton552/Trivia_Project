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
		sqlQuery("CREATE TABLE IF NOT EXISTS QUESTIONS (QUESTION TEXT, CORRECT_ANSWER TEXT NOT NULL, INCCORRECT_ANSWER1 TEXT NOT NULL, INCCORRECT_ANSWER2 TEXT NOT NULL, INCCORRECT_ANSWER3 TEXT NOT NULL);");
	}

	createQuestionDataBase();

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

list<Question> SqliteDatabase::getQuestions(const int numOfQuestions)
{

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

/// <summary>
/// the function fills the question database with questions from web site
/// </summary>
/// <returns>0 - every thing is fine, 1 - something went wrong</returns>
int SqliteDatabase::createQuestionDataBase()
{
	IStream* stream;
	//Also works with https URL's - unsure about the extent of SSL support though.
	HRESULT result = URLOpenBlockingStream(0, L"https://opentdb.com/api.php?amount=10&type=multiple", &stream, 0, 0);
	if (result != 0)
	{
		return 1;
	}
	char buffer[100];
	unsigned long bytesRead;
	std::stringstream ss;
	stream->Read(buffer, 100, &bytesRead);
	while (bytesRead > 0U)
	{
		ss.write(buffer, (long long)bytesRead);
		stream->Read(buffer, 100, &bytesRead);
	}
	stream->Release();
	string resultString = ss.str();

	json data;
	std::stringstream(resultString) >> data;

	try
	{
		string question;
		string correctAnswer;
		string inccorrectAnswer1;
		string inccorrectAnswer2;
		string inccorrectAnswer3;

		for (int i = 0; i < NUM_OF_QUESTIONS; i++)
		{
			for (json::iterator it = data["results"][i].begin(); it != data["results"][i].end(); ++it)
			{
				if (it.key() == "question")
				{
					question = it.value();
				}

				if (it.key() == "correct_answer")
				{
					correctAnswer = it.value();
				}

				if (it.key() == "incorrect_answers")
				{
					inccorrectAnswer1 = it.value()[0];
					inccorrectAnswer2 = it.value()[1];
					inccorrectAnswer3 = it.value()[2];
				}
			}
			
			string query = "INSERT INTO QUESTIONS VALUES (\"" + question + "\", \"" + correctAnswer + "\", \"" + inccorrectAnswer1 + "\", \"" + inccorrectAnswer2 + "\", \"" + inccorrectAnswer3 + "\");";
			sqlQuery(query.c_str());
		}
	}
	catch (exception& e)
	{
		cout << "Error has occurred: " << e.what() << endl;
	}

	return 0;
}