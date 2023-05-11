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
	void signup(const string username, const string password, const string email);
	void login(const string username, const string password);
	void logout(const string username);

private:
	//Fields
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;
};

