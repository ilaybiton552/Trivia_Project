#pragma once
#include <string>

using std::string;

class LoggedUser
{
public:
	//Getter
	string getUsername() const;

private:
	//Field
	string m_username;
};

