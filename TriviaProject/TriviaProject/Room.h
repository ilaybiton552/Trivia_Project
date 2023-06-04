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
	Room();
	Room(RoomData roomData); //c'tor
	~Room(); // d'tor
	bool addUser(const LoggedUser loggedUser);
	bool removeUser(const  LoggedUser loggedUser);
	//Getters
	vector<string> getAllUsers() const;
	RoomData getRoomData() const;

	void setIsActive(const unsigned int isActive);

private:
	//Fields
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};

