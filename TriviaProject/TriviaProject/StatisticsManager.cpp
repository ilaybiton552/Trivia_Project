#include "StatisticsManager.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="database">pointer of IDatabase, the database of the server</param>
StatisticsManager::StatisticsManager(IDatabase* database)
{
}

/// <summary>
/// Gets the 5 best scores
/// </summary>
/// <returns>vector of pairs of string and int, string - the username, int - the score</returns>
vector<pair<string, int>> StatisticsManager::getHighScore()
{
    return vector<pair<string, int>>();
}

/// <summary>
/// Gets statistics of a user
/// </summary>
/// <param name="username">string, the username</param>
/// <returns>vector of float, the statistics</returns>
vector<float> StatisticsManager::getUserStatistics(const string& username)
{
    return vector<float>();
}
