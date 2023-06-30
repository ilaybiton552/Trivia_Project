#pragma once
#pragma comment(lib, "urlmon.lib")

#include "json.hpp"
#include <urlmon.h>
#include <sstream>
#include <iostream>
#include <exception>
#include <vector>
#include <io.h>
#include <algorithm>
#include <string>
#include "Question.h"
#include "IDatabase.h"
#include "sqlite3.h"

#define DB_FILE_NAME "Trivia_DataBase.sqlite"
#define NUM_OF_QUESTIONS 10

using std::string;
using std::cout;
using std::endl;
using std::vector;
using nlohmann::json;
using std::exception;

class SqliteDatabase : public IDatabase
{
public:
	//Methods
	virtual bool open() override;
	virtual bool close() override;
	virtual int doesUserExist(const string username) override;
	virtual int doesPasswordMatch(const string username, const string password) override;
	virtual int addNewUser(const string username, const string password, const string email, const string address, const string phone, const string birthDate) override;
	virtual float getPlayerAverageTime(const string& username) override;
	virtual int getNumOfCorrectAnswers(const string& username) override;
	virtual int getNumOfTotalAnswers(const string& username) override;
	virtual int getNumOfTotalGames(const string& username) override;
	virtual int getPlayerScore(const string& username) override;
	virtual vector<string> getHighScores() override;
	virtual list<Question> getQuestions(const int numOfQuestions) override;
	virtual unsigned int getLastGameId() override;
	virtual bool addGame() override;
	virtual bool submitUserAnswer(const string& username, const int isCorrect, const float answerTime, const int gameId) override;

private:
	//Field
	sqlite3* m_database;

	//Method
	bool sqlQuery(const char* sqlStatement, int(*callback)(void*, int, char**, char**) = nullptr, void* callbackArgument = nullptr);
	static int getUserInfo(void* data, int argc, char** argv, char** azColName);
	static int returnOneNumber(void* data, int argc, char** argv, char** azColName);
	static int returnOneFloat(void* data, int argc, char** argv, char** azColName);
	static int getUsernames(void* data, int argc, char** argv, char** azColName);
	int createQuestionDataBase();
	static int getQuestions(void* data, int argc, char** argv, char** azColName);
};

