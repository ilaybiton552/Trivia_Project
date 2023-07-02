#include "LoginManager.h"
#include "UserInfoCheck.h"

/// <summary>
/// Constructor of LoginManager
/// </summary>
/// <param name="database">pointer of IDatabase, the database of the server</param>
LoginManager::LoginManager(IDatabase* database)
{
	m_database = database;
}

/// <summary>
/// destructor
/// </summary>
LoginManager::~LoginManager()
{
	this->m_loggedUsers.clear();
}

/// <summary>
/// the function signups the user
/// </summary>
/// <param name="username">the username</param>
/// <param name="password">the password</param>
/// <param name="email">the email</param>
/// <param name="address">string, the address</param>
/// <param name="phoneNumber">string, phone number</param>
/// <param name="birthdate">string, date of birth</param>
/// <returns>the result code</returns>
int LoginManager::signup(const string username, const string password, const string email, const string address, const string phoneNumber, const string birthdate)
{
	if (!UserInfoCheck::checkUserInfo(username, password, email, address, phoneNumber, birthdate))
	{
		return REGEX_ERROR;
	}
	if (m_database->doesUserExist(username)) // check if the username doesn't exist in the database
	{
		return USER_ALREADY_EXIST_CODE;
	}

	m_database->addNewUser(username, password, email, address, phoneNumber, birthdate); // add new user to the database
	m_loggedUsers.push_back(LoggedUser(username)); // add the user to the logged user list
	return SUCCESS_CODE;
}

/// <summary>
/// the function logins the user
/// </summary>
/// <param name="username">the username</param>
/// <param name="password">the password</param>
/// <returns>the result code</returns>
int LoginManager::login(const string username, const string password)
{
	if (!m_database->doesUserExist(username)) // check if the user exists in the database
	{
		return USER_DOES_NOT_EXIST_CODE;
	}
	else if (!m_database->doesPasswordMatch(username, password)) // check if the password doesn't match the username
	{
		return WRONG_PASSWORD_CODE;
	}
	else if (findLoggedUser(username) != nullptr) // check if the user already logged
	{
		return USER_ALREADY_LOGGED_CODE;
	}

	m_loggedUsers.push_back(LoggedUser(username)); // add the user to the logged user list
	return SUCCESS_CODE;
}

/// <summary>
/// the function logouts the user
/// </summary>
/// <param name="username">the username</param>
/// <returns>the result code</returns>
int LoginManager::logout(const string username)
{
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it)
	{
		if (it->getUsername() == username)
		{
			m_loggedUsers.erase(it);
			return SUCCESS_CODE;
		}
	}
	return USER_DOES_NOT_LOGGED_CODE;
}

/// <summary>
/// the function return pointer to logged user
/// </summary>
/// <param name="username">the logged user username to find</param>
/// <returns>pointer to logged user</returns>
LoggedUser* LoginManager::findLoggedUser(const string username) const
{
	for (LoggedUser loggedUser : m_loggedUsers)
	{
		if (loggedUser.getUsername() == username)
		{
			return &loggedUser;
		}
	}

	return nullptr;
}