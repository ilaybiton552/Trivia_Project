#include "Game.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="questions">vector of questions</param>
/// <param name="players">vector of players</param>
/// <param name="gameId">unsigned int, the id of the game</param>
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
/// <return>unsigned int, the correct answer id</return>
unsigned int Game::submitAnswer(LoggedUser player, unsigned int answerId, float answerTime, IDatabase* database)
{
	int isCorrect = 0;
	unsigned int correctId = m_players[player].currentQuestion.getCorrectAnswerId();
	if (correctId == answerId)
	{
		m_players[player].correctAnswerCount++;
		isCorrect = 1;
	}
	else
	{
		m_players[player].wrongAnswerCount++;
	}
	m_players[player].averageAnswerTime += answerTime;
	m_players[player].averageAnswerTime /= 2; // calculate the average time per question
	
	// push the answer to the database
	database->submitUserAnswer(player.getUsername(), isCorrect, answerTime, this->m_gameId);

	return correctId;
}

/// <summary>
/// the function removes the player from the game
/// </summary>
/// <param name="player">the player to remove</param>
void Game::removePlayer(LoggedUser player)
{
	this->m_answeredQuestions.erase(player);
}

/// <summary>
/// Gets the results of the players
/// </summary>
/// <returns>vector of PlayerResults, the result of the players</returns>
vector<PlayerResults> Game::getPlayersResults() const
{
	vector<PlayerResults> playersResults;

	for (auto it = m_players.begin(); it != m_players.end(); ++it)
	{
		PlayerResults results = { it->first.getUsername(), it->second.correctAnswerCount, it->second.wrongAnswerCount, it->second.averageAnswerTime };
		playersResults.push_back(results);
	}

	return playersResults;
}

/// <summary>
/// the function returns the game id
/// </summary>
/// <returns>game id</returns>
unsigned int Game::getGameId() const
{
	return m_gameId;
}
