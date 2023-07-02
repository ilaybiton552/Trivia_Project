#include "LoggedUser.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="username">the logged username</param>
LoggedUser::LoggedUser(const string username)
{
	this->m_username = username;
}

/// <summary>
/// the function returns the username
/// </summary>
/// <returns>the username</returns>
string LoggedUser::getUsername() const
{
	return this->m_username;
}

/// <summary>
/// Operator <
/// </summary>
/// <param name="user1">LoggedUser, the first user to comapre</param>
/// <param name="user2">LoggedUser, the second user to compare</param>
/// <returns>bool, if the first user is less than the second user</returns>
bool operator<(const LoggedUser& user1, const LoggedUser& user2)
{
	return user1.m_username < user2.m_username;
}
