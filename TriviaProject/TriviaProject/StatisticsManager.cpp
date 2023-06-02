#include "StatisticsManager.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="database">pointer of IDatabase, the database of the server</param>
StatisticsManager::StatisticsManager(IDatabase* database)
{
    m_database = database;
}

/// <summary>
/// Gets the 5 best scores
/// </summary>
/// <returns>vector of pairs of string and int, string - the username, int - the score</returns>
vector<string> StatisticsManager::getHighScore()
{
    return m_database->getHighScores();
}

/// <summary>
/// Gets statistics of a user
/// </summary>
/// <param name="username">string, the username</param>
/// <returns>vector of float, the statistics</returns>
vector<float> StatisticsManager::getUserStatistics(const string& username)
{
    vector<float> userStatistics; //[num of games, num of correct answers, num of wrong answers, average time to answer a question]

    userStatistics.push_back(m_database->getNumOfTotalGames(username));
    userStatistics.push_back(m_database->getNumOfCorrectAnswers(username));
    userStatistics.push_back(m_database->getNumOfTotalAnswers(username) - m_database->getNumOfCorrectAnswers(username));
    userStatistics.push_back(m_database->getPlayerAverageTime(username));

    return userStatistics;
}
