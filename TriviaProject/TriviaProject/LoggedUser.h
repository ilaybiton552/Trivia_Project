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

private:
	//Field
	string m_username;
};

