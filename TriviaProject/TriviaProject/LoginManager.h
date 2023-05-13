#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "IDatabase.h"
#include "LoggedUser.h"

enum loginCodes {SUCCESS_CODE, USER_DOES_NOT_EXIST_CODE, USER_ALREADY_EXIST_CODE, WRONG_PASSWORD_CODE, USER_ALREADY_LOGGED_CODE, USER_DOES_NOT_LOGGED_CODE};

using std::vector;
using std::string;

class LoginManager
{
public:
	//Methods
	~LoginManager(); // d'tor
	int signup(const string username, const string password, const string email);
	int login(const string username, const string password);
	int logout(const string username);

private:
	//Fields
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;

	//Method
	LoggedUser* findLoggedUser(const string username) const;
};

