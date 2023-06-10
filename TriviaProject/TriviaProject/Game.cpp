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
	return question;
}

/// <summary>
/// the function submits user's answer
/// </summary>
/// <param name="player">the user</param>
/// <param name="gameData">the submited answer game data</param>
void Game::submitAnswer(LoggedUser player, GameData gameData)
{
	this->m_players[player] = gameData;
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
