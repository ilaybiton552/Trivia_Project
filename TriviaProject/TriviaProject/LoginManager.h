#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "IDatabase.h"
#include "LoggedUser.h"

enum loginCodes {SUCCESS_CODE = 1, USER_DOES_NOT_EXIST_CODE, USER_ALREADY_EXIST_CODE, WRONG_PASSWORD_CODE, USER_ALREADY_LOGGED_CODE, USER_DOES_NOT_LOGGED_CODE, REGEX_ERROR};

using std::vector;
using std::string;

class LoginManager
{
public:
	//Methods
	LoginManager(IDatabase* database);
	~LoginManager(); // d'tor
	int signup(const string username, const string password, const string email, const string address, const string phoneNumber, const string birthdate);
	int login(const string username, const string password);
	int logout(const string username);

private:
	//Fields
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;

	//Method
	LoggedUser* findLoggedUser(const string username) const;
};

