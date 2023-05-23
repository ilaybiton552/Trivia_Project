#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "Question.h"

using std::string;
using std::vector;
using std::pair;
using std::list;

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const string username) = 0;
	virtual int doesPasswordMatch(const string username, const string password) = 0;
	virtual int addNewUser(const string username, const string password, const string email, const string address, const string phone, const string birthDate) = 0;
	virtual float getPlayerAverageTime(const string& username) = 0;
	virtual int getNumOfCorrectAnswers(const string& username) = 0;
	virtual int getNumOfTotalAnswers(const string& username) = 0;
	virtual int getNumOfTotalGames(const string& username) = 0;
	virtual int getPlayerScore(const string& username) = 0;
	virtual vector<pair<string, int>> getHighScores() = 0;
	virtual list<Question> getQuestions(const int numOfQuestions) = 0;
};

