#pragma once
#include <string>
#include <vector>
#include <algorithm>

using std::string; 
using std::vector;

class Question
{
public:
	//Methods
	Question();
	Question(const string question, const string correctAnswer, const string inccorrectAnswer1, const string inccorrectAnswer2, const string inccorrectAnswer3);
	string getQuestion() const;
	vector<string> getPossibleAnswers() const;
	int getCorrectAnswerId() const;
private:
	string m_question;
	vector<string> m_possibleAnswers;
	int m_correctAnswerId;
};

