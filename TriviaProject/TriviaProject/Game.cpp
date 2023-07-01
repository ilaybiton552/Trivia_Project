#include "Game.h"
#include <Windows.h>

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
	while (m_answeredQuestions.size() != 1 && !areAllUsersAnswered()) // more than 1 player remains
	{
		Sleep(WAIT_FOR_ALL_PLAYERS);
	}
	Question question = this->m_questions.at(m_answeredQuestions[player]);
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

	m_answeredQuestions[player]++;

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
vector<PlayerResults> Game::getPlayersResults()
{
	vector<PlayerResults> playersResults;

	if (m_answeredQuestions.begin()->second < m_questions.size()) // didn't finish questions
	{
		throw std::exception("Didn't finish the game");
	}
	for (auto it = m_players.begin(); it != m_players.end(); ++it)
	{
		PlayerResults results;
		results.username = it->first.getUsername();
		results.correctAnswerCount = it->second.correctAnswerCount;
		results.wrongAnswerCount = it->second.wrongAnswerCount;
		results.averageAnswerTime = it->second.averageAnswerTime;
		playersResults.push_back(results);
	}

	return playersResults;
}

/// <summary>
/// the function returns the game id
/// </summary>
/// <returns>game id</returns>
unsigned int Game::getGameId()
{
	return m_gameId;
}

/// <summary>
/// the function return if all of the users answered the question
/// </summary>
/// <returns>if all the users answered the question</returns>
bool Game::areAllUsersAnswered()
{
	unsigned int firstNumOfAnswers = m_answeredQuestions.begin()->second;

	for (auto it = m_answeredQuestions.begin(); it != m_answeredQuestions.end(); ++it)
	{
		if (firstNumOfAnswers != it->second)
		{
			return false;
		}
	}

	return true;
}