#pragma once
#include <string>

using std::string;

class LoggedUser
{
public:
	//Methods
	LoggedUser(const string username); // c'tor
	//Getter
	string getUsername() const;
	friend bool operator<(const LoggedUser& user1, const LoggedUser& user2);

private:
	//Field
	string m_username;
};

