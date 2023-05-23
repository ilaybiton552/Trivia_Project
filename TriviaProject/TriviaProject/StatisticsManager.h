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
	//Methods
	StatisticsManager(IDatabase* database); // c'tor

	vector<pair<string, int>> getHighScore();
	vector<float> getUserStatistics(const string& username);

private:
	//Field
	IDatabase* m_database;
};
