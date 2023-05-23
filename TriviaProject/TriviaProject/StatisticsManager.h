#pragma once
#include "IDatabase.h"
#include <vector>
#include <string>

using std::vector;
using std::pair;
using std::string;

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database);

	vector<pair<string, int>> getHighScore();
	vector<float> getUserStatistics(const string& username);

private:
	IDatabase* m_database;
};

