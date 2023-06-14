#include "GameManager.h"

Game GameManager::createGame(Room room)
{
	unsigned int gameId = m_database->getLastGameId() + 1;
	m_database->addGame();

	list<Question> questionsList = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);
	vector<Question> questionsVector;
	for (Question question : questionsList) // convert the question list to vector
	{
		questionsVector.push_back(question);
	}

	Game game(questionsVector, room.getUsers(), gameId);
	m_games.push_back(game);
}

/// <summary>
/// the function deletes the game according to its id
/// </summary>
/// <param name="gameId">the id of the game to delete</param>
void GameManager::deleteGame(unsigned int gameId)
{
	for (auto it = m_games.begin(); it != m_games.end(); it++)
	{
		if ((*it).getGameId() == gameId)
		{
			m_games.erase(it);
		}
	}
}