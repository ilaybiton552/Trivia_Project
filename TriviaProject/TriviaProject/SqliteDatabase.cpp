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
		sqlQuery("CREATE TABLE IF NOT EXISTS GAMES (ID INTEGER PRIMARY KEY AUTOINCREMENT);");
		sqlQuery("CREATE TABLE IF NOT EXISTS STATISTICS (USERNAME TEXT NOT NULL, IS_CORRECT_ANSWER INTEGER NOT NULL, ANSWER_TIME REAL NOT NULL, GAME_ID INTEGER NOT NULL, FOREIGN KEY(USERNAME) REFERENCES USERS(USERNAME), FOREIGN KEY(GAME_ID) REFERENCES GAMES(ID));");
		sqlQuery("CREATE TABLE IF NOT EXISTS QUESTIONS (QUESTION TEXT NOT NULL, CORRECT_ANSWER TEXT NOT NULL, INCORRECT_ANSWER1 TEXT NOT NULL, INCORRECT_ANSWER2 TEXT NOT NULL, INCORRECT_ANSWER3 TEXT NOT NULL);");
		createQuestionDataBase();
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
	float sum = 0;
	int numOfAns = 0;
	string query = "SELECT COUNT(CASE WHEN USERNAME IS \""+ username + "\" THEN ANSWER_TIME END) FROM STATISTICS;";
	sqlQuery(query.c_str(), returnOneNumber, &numOfAns);
	query = "SELECT SUM(ANSWER_TIME) FROM STATISTICS WHERE (USERNAME IS \"" + username + "\");";
	sqlQuery(query.c_str(), returnOneFloat, &sum);

	if (numOfAns != 0) // user played games
	{
		return (sum / numOfAns);
	}
	return 0;
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
vector<string> SqliteDatabase::getHighScores()
{
	vector<string> usernames;
	vector<string> scores; // will be username,score;username,score
	string currScore;
	// get all usernames sorted by highest score (limit of 5)
	sqlQuery("SELECT USERNAME FROM STATISTICS WHERE IS_CORRECT_ANSWER = 1 GROUP BY USERNAME ORDER BY COUNT(IS_CORRECT_ANSWER) DESC LIMIT 3;", getUsernames, &usernames);

	for (int i = 0; i < usernames.size(); i++) // create the scores vector with the wanted data
	{
		currScore += usernames[i];
		currScore += ',';
		currScore += std::to_string(getPlayerScore(usernames[i]));
		scores.push_back(currScore);
		currScore.clear();
	}

	return scores;
}

/// the function returns list of questions
/// </summary>
/// <param name="numOfQuestions">number of wanted questions</param>
/// <returns>list of questions</returns>
list<Question> SqliteDatabase::getQuestions(const int numOfQuestions)
{
	list<Question> questions;
	sqlQuery(("SELECT * FROM QUESTIONS LIMIT " + std::to_string(numOfQuestions) + ';').c_str(), getQuestions, &questions);
	return questions;
}

/// <summary>
/// Gets from the data base the last game id
/// </summary>
/// <returns>unsigned int, the last game id</returns>
unsigned int SqliteDatabase::getLastGameId()
{
	unsigned int lastId = 0;
	sqlQuery("SELECT * FROM GAMES ORDER BY ID DESC LIMIT 1;", returnOneNumber, &lastId);
	return lastId;
}

/// <summary>
/// Adds a game to the database
/// </summary>
/// <returns>bool, if succeeded to add the game</returns>
bool SqliteDatabase::addGame()
{
	return sqlQuery("INSERT INTO GAMES SELECT NULL;");
}

/// <summary>
/// Submits a user answer to the database
/// </summary>
/// <param name="username">string, the username</param>
/// <param name="isCorrect">int, if the answer is correct: 1 - correct, 0 - incorrect</param>
/// <param name="answerTime">float, the time it took the user to answer</param>
/// <param name="gameId">int the id of the game</param>
/// <returns></returns>
bool SqliteDatabase::submitUserAnswer(const string& username, const int isCorrect, const float answerTime, const int gameId)
{
	string query("INSERT INTO STATISTICS SELECT '" + username + "', " + std::to_string(isCorrect) + 
		", " + std::to_string(answerTime) + ", " + std::to_string(gameId) + ';');
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

/// <summary>
/// the function converts sql data to int
/// </summary>
int SqliteDatabase::returnOneNumber(void* data, int argc, char** argv, char** azColName)
{
	if (argv[0] != nullptr)
	{
		*static_cast<int*>(data) = std::atoi(argv[0]);
	}

	return 0;
}

/// <summary>
/// the function converts sql data to float
/// </summary>
int SqliteDatabase::returnOneFloat(void* data, int argc, char** argv, char** azColName)
{
	if (argv[0] != nullptr)
	{
		*static_cast<float*>(data) = std::stof(argv[0]);
	}
	
	return 0;
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
		string incorrectAnswer1;
		string incorrectAnswer2;
		string incorrectAnswer3;

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
					incorrectAnswer1 = it.value()[0];
					incorrectAnswer2 = it.value()[1];
					incorrectAnswer3 = it.value()[2];
				}
			}
			// insert the data into the table
			string query = "INSERT INTO QUESTIONS VALUES (\"" + question + "\", \"" + correctAnswer + "\", \"" + incorrectAnswer1 + "\", \"" + incorrectAnswer2 + "\", \"" + incorrectAnswer3 + "\");";
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
	vector<string>* usernames = static_cast<vector<string>*> (data);

	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == string("USERNAME"))
		{
			usernames->push_back(argv[i]);
		}
	}

	return 0;
}

/// the function convets the sql data to list with questions
/// </summary>
int SqliteDatabase::getQuestions(void* data, int argc, char** argv, char** azColName)
{
	list<Question>* questions = static_cast<list<Question>*>(data);

	string question;
	string correctAnswer;
	string incorrectAnswer1;
	string incorrectAnswer2;
	string incorrectAnswer3;

	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "QUESTION")
		{
			question = argv[i];
		}
		else if (string(azColName[i]) == "CORRECT_ANSWER")
		{
			correctAnswer = argv[i];
		}
		else if (string(azColName[i]) == "INCORRECT_ANSWER1")
		{
			incorrectAnswer1 = argv[i];
		}
		else if (string(azColName[i]) == "INCORRECT_ANSWER2")
		{
			incorrectAnswer2 = argv[i];
		}
		else if (string(azColName[i]) == "INCORRECT_ANSWER3")
		{
			incorrectAnswer3 = argv[i];
		}
	}
	questions->push_back(Question(question, correctAnswer, incorrectAnswer1, incorrectAnswer2, incorrectAnswer3));
	return 0;
}

