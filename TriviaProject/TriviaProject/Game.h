#pragma once
#include <vector>
#include <map>
#include "Question.h"
#include "LoggedUser.h"
#include "Structs.h"
#include "Room.h"
#include "IDatabase.h"

using std::vector;
using std::map;
using std::pair;

class Game
{
public:
	// Methods
	Game(vector<Question> questions, vector<LoggedUser> players, unsigned int gameId); // c'tor

	Question getQuestionForUser(LoggedUser player);
	unsigned int submitAnswer(LoggedUser player, unsigned int answerId, float answerTime, IDatabase* database);
	void removePlayer(LoggedUser player);
	vector<PlayerResults> getPlayersResults();
	unsigned int getGameId();

private:
	// Fields
	vector<Question> m_questions;
	map<LoggedUser, unsigned int> m_answeredQuestions;
	map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;
};

