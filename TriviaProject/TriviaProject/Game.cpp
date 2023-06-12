#include "Game.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="questions">vector of questions</param>
/// <param name="players">vector of players</param>
/// <param name="gameId"></param>
Game::Game(vector<Question> questions, vector<LoggedUser> players, unsigned int gameId)
{
	m_questions = questions;
	m_gameId = gameId;

	for (int i = 0; i < players.size(); i++)
	{
		m_answeredQuestions[players[i]] = 0;
	}
}

/// <summary>
/// the function returns a question for the user
/// </summary>
/// <param name="player">the user</param>
/// <returns>the question for the user</returns>
Question Game::getQuestionForUser(LoggedUser player)
{
	Question question = this->m_questions[m_answeredQuestions[player]];
	m_answeredQuestions[player]++;
	m_players[player].currentQuestion = question;
	return question;
}

/// <summary>
/// the function submits user's answer
/// </summary>
/// <param name="player">the user</param>
/// <param name="answerId">the submited answer id</param>
/// <param name="answerTime">the answer time</param>
/// <param name="database">the database</param>
void Game::submitAnswer(LoggedUser player, unsigned int answerId, float answerTime, IDatabase* database)
{
	if (m_players[player].currentQuestion.getCorrectAnswerId() == answerId)
	{
		m_players[player].correctAnswerCount++;
	}
	else
	{
		m_players[player].wrongAnswerCount++;
	}
}

/// <summary>
/// the function removes the player from the game
/// </summary>
/// <param name="player">the player to remove</param>
void Game::removePlayer(LoggedUser player)
{
	this->m_players.erase(player);
	this->m_answeredQuestions.erase(player);
}

/// <summary>
/// the function returns the game id
/// </summary>
/// <returns>game id</returns>
unsigned int Game::getGameId() const
{
	return m_gameId;
}
