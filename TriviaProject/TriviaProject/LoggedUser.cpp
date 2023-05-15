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