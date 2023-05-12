#pragma once
#include <string>
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

using std::vector;
using std::string;

class LoginManager
{
public:
	//Methods
	int signup(const string username, const string password, const string email);
	int login(const string username, const string password);
	int logout(const string username);

private:
	//Fields
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;
};

