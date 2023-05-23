#include "Question.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="question">the question</param>
/// <param name="correctAnswer">the correct answer</param>
/// <param name="inccorrectAnswer1">inccorrect answer</param>
/// <param name="inccorrectAnswer2">inccorrect answer</param>
/// <param name="inccorrectAnswer3">inccorrect answer</param>
Question::Question(const string question, const string correctAnswer, const string inccorrectAnswer1, const string inccorrectAnswer2, const string inccorrectAnswer3)
{
	this->m_question = question;
	this->m_possibleAnswers.push_back(correctAnswer);
	this->m_possibleAnswers.push_back(inccorrectAnswer1);
	this->m_possibleAnswers.push_back(inccorrectAnswer2);
	this->m_possibleAnswers.push_back(inccorrectAnswer3);

	std::sort(this->m_possibleAnswers.begin(), this->m_possibleAnswers.end()); // sort the vector to randomize the possible answers
	
	for (int i = 0; i < m_possibleAnswers.size(); i++) // find the correct answer id
	{
		if (m_possibleAnswers[i] == correctAnswer)
		{
			this->m_correctAnswerId = i;
		}
	}
}

/// <summary>
/// the function returns the question
/// </summary>
/// <returns>the question</returns>
string Question::getQuestion() const
{
	return this->m_question;
}

/// <summary>
/// the function returns vector of possible answers
/// </summary>
/// <returns>vector of possible answers</returns>
vector<string> Question::getPossibleAnswers() const
{
	return this->m_possibleAnswers;
}

/// <summary>
/// the function returns the correct answer id
/// </summary>
/// <returns>the correct answer id</returns>
int Question::getCorrectAnswerId() const
{
	return this->m_correctAnswerId;
}