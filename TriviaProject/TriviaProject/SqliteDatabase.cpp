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
		sqlQuery("CREATE TABLE IF NOT EXISTS STATISTICS (USERNAME TEXT NOT NULL, IS_CORRECT_ANSWER INTEGER NOT NULL, ANSWER_TIME REAL NOT NULL, GAME_ID INTEGER NOT NULL, FOREIGN KEY(USERNAME) REFERENCES USERS(USERNAME)); ");
		sqlQuery("CREATE TABLE IF NOT EXISTS QUESTIONS (QUESTION TEXT NOT NULL, CORRECT_ANSWER TEXT NOT NULL, INCCORRECT_ANSWER1 TEXT NOT NULL, INCCORRECT_ANSWER2 TEXT NOT NULL, INCCORRECT_ANSWER3 TEXT NOT NULL);");
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

/// <summary>
/// Gets the average time of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>float, the username's average answer time</returns>
float SqliteDatabase::getPlayerAverageTime(const string& username)
{
	float sum;
	int numOfAns;
	string query = "SELECT COUNT(CASE WHEN USERNAME IS \""+ username + "\" THEN ANSWER_TIME END) FROM STATISTICS;";
	sqlQuery(query.c_str(), returnOneNumber, &numOfAns);
	query = "SELECT SUM(ANSWER_TIME) FROM STATISTICS WHERE (USERNAME IS \"" + username + "\");";
	sqlQuery(query.c_str(), returnOneFloat, &sum);

	return (sum/numOfAns);
}

/// <summary>
/// Gets the number of correct answers of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the number of correct answers of the player</returns>
int SqliteDatabase::getNumOfCorrectAnswers(const string& username)
{
	int numOfCorrectAnswers;
	string query = "SELECT COUNT(CASE WHEN USERNAME IS \"" + username + "\" AND IS_CORRECT_ANSWER IS 1 THEN IS_CORRECT_ANSWER END) FROM STATISTICS;";
	sqlQuery(query.c_str(), returnOneNumber, &numOfCorrectAnswers);

	return numOfCorrectAnswers;
}

/// <summary>
/// Gets the number of total answers of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the number of total answers of the player</returns>
int SqliteDatabase::getNumOfTotalAnswers(const string& username)
{
	int numOfAnswers;
	string query = "SELECT COUNT(CASE WHEN USERNAME IS \"" + username + "\" THEN IS_CORRECT_ANSWER END) FROM STATISTICS;";
	sqlQuery(query.c_str(), returnOneNumber, &numOfAnswers);

	return numOfAnswers;
}

/// <summary>
/// Gets the number of total games of a player
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the number of games answers of the player</returns>
int SqliteDatabase::getNumOfTotalGames(const string& username)
{
	int numOfTotalGames;
	string query = "SELECT COUNT(DISTINCT GAME_ID) FROM STATISTICS WHERE USERNAME IS \"" + username + "\";";
	sqlQuery(query.c_str(), returnOneNumber, &numOfTotalGames);

	return numOfTotalGames;
}

/// <summary>
/// Gets a playre's score
/// </summary>
/// <param name="username">string, the username of the player</param>
/// <returns>int, the score of the player</returns>
int SqliteDatabase::getPlayerScore(const string& username)
{
	return getNumOfCorrectAnswers(username);
}

/// <summary>
/// Gets the high scores
/// </summary>
/// <returns>vector of string, vector of users with high scores</returns>
vector<pair<string, int>> SqliteDatabase::getHighScores()
{
	vector<string> usernames;
	vector<pair<string, int>> scores; // <username, score>
	sqlQuery("SELECT * FROM USERS;", getUsernames, &usernames); // get all the usernames

	for (int i = 0; i < usernames.size(); i++) // create the scores vector with the wanted data
	{
		scores.push_back(pair<string, int>(usernames[i], getPlayerScore(usernames[i])));
	}
	// sort the vector according to the scores 
	std::sort(scores.begin(), scores.end(), [](const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second; });

	return scores;
}

/// the function returns list of questions
/// </summary>
/// <param name="numOfQuestions">number of wanted questions</param>
/// <returns>list of questions</returns>
list<Question> SqliteDatabase::getQuestions(const int numOfQuestions)
{
	list<Question> questions;
	sqlQuery("SELECT * FROM QUESTIONS;", getQuestions, &questions);

	for (int i = 0; i < (questions.size() - numOfQuestions); i++) // shorten the list of question 
	{
		questions.pop_front();
	}

	return questions;
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
/// the function converts sql data to int
/// </summary>
int SqliteDatabase::returnOneNumber(void* data, int argc, char** argv, char** azColName)
{
	if (isdigit(argv[0][0]))
	{
		*static_cast<int*>(data) = int(argv[0]);
	}
	else
	{
		*static_cast<int*>(data) = int(argv[1]);
	}
	return 0;
}

/// <summary>
/// the function converts sql data to float
/// </summary>
int SqliteDatabase::returnOneFloat(void* data, int argc, char** argv, char** azColName)
{
	if (isdigit(argv[0][0]))
	{
		*static_cast<float*>(data) = std::stof(argv[0]);
	}
	else
	{
		*static_cast<float*>(data) = std::stof(argv[1]);
	}
}

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
	while (bytesRead > 0U) // get the data from the site and put in the variable ss
	{
		ss.write(buffer, (long long)bytesRead); 
		stream->Read(buffer, 100, &bytesRead);
	}
	stream->Release();
	string resultString = ss.str();

	json data;
	std::stringstream(resultString) >> data; // create the json with the questions

	try
	{
		string question;
		string correctAnswer;
		string inccorrectAnswer1;
		string inccorrectAnswer2;
		string inccorrectAnswer3;

		for (int i = 0; i < NUM_OF_QUESTIONS; i++) // put the question in the database
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
			// insert the data into the table
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

/// <summary>
/// the function converts the sql data to vector of usernames
/// </summary>

int SqliteDatabase::getUsernames(void* data, int argc, char** argv, char** azColName)
{
	vector<string> usernames;

	for (int i = 0; i < argc; i++)
	{
		if (azColName[i] == "USERNAME")
		{
			usernames.push_back(argv[i]);
		}
	}

	*(static_cast<vector<string>*> (data)) = usernames;

	return 0;
}

/// the function convets the sql data to list with questions
/// </summary>
int SqliteDatabase::getQuestions(void* data, int argc, char** argv, char** azColName)
{
	list<Question> questions;

	string question;
	string correctAnswer;
	string inccorrectAnswer1;
	string inccorrectAnswer2;
	string inccorrectAnswer3;

	for (int i = 0; i < argc; i++)
	{
		if (azColName[i] == "QUESTION")
		{
			question = argv[i];
		}
		else if (azColName[i] == "CORRECT_ANSWER")
		{
			correctAnswer = (int(argv[i]));
		}
		else if (azColName[i] == "INCCORRECT_ANSWER1")
		{
			inccorrectAnswer1 = argv[i];
		}
		else if (azColName[i] == "INCCORRECT_ANSWER2")
		{
			inccorrectAnswer2 = argv[i];
		}
		else if (azColName[i] == "INCCORRECT_ANSWER3")
		{
			inccorrectAnswer3 = argv[i];
		}

		if (i % 4 == 0 && i != 0)
		{
			questions.push_back(Question(question, correctAnswer, inccorrectAnswer1, inccorrectAnswer2, inccorrectAnswer3));
		}
	}

	questions.push_back(Question(question, correctAnswer, inccorrectAnswer1, inccorrectAnswer2, inccorrectAnswer3));

	*(static_cast<list<Question>*>(data)) = questions;

	return 0;
}

