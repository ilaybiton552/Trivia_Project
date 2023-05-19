#pragma once
#include <vector>
#include <string>
#include "LoggedUser.h"
#include "Structs.h"

using std::vector;
using std::string;

class Room
{
public:
	//Methods
	bool addUser(const LoggedUser loggedUser);
	bool removeUser(const  LoggedUser loggedUser);
	vector<string> getAllUsers() const;

private:
	//Fields
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};

