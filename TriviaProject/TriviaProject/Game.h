#pragma once
#include <vector>
#include <map>
#include "Question.h"
#include "LoggedUser.h"
#include "Structs.h"

using std::vector;
using std::map;

class Game
{
public:
	// Methods
	Question getQuestionForUser(LoggedUser loggedUser);
	void submitAnswer(LoggedUser loggedUser, GameData gameData);
	void removePlayer(LoggedUser loggedUser);

private:
	// Fields
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;
};

