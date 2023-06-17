#pragma once
#include <vector>
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"

using std::vector;

class GameManager
{
public:
	GameManager(IDatabase* database);

	// Methods
	Game createGame(Room room);
	void deleteGame(unsigned int gameId);

private:
	// Fields
	IDatabase* m_database;
	vector<Game> m_games;
};

