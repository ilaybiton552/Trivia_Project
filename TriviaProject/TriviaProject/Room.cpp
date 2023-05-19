#include "Room.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="roomData">the room data</param>
Room::Room(RoomData roomData)
{
	this->m_metadata = roomData;
}

/// <summary>
/// Desructor
/// </summary>
Room::~Room()
{
	this->m_users.clear();
}

/// <summary>
/// the function adds user to the room
/// </summary>
/// <param name="loggedUser">the logged user to add</param>
/// <returns>if the user is added</returns>
bool Room::addUser(const LoggedUser loggedUser)
{
	for (LoggedUser user : m_users) // check if the user is not in the room
	{
		if (user.getUsername() == loggedUser.getUsername())
		{
			return false;
		}
	}

	m_users.push_back(loggedUser); // add the user to the room
	return true;
}

/// <summary>
/// the function removes user from the room
/// </summary>
/// <param name="loggedUser">the user to remove</param>
/// <returns>if the user is removed</returns>
bool Room::removeUser(const  LoggedUser loggedUser)
{
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->getUsername() == loggedUser.getUsername())
		{
			m_users.erase(it); // remove the user from the room
			return true;
		}
	}
	return false; // the user not found
}

/// <summary>
/// the function returns all the users in the room
/// </summary>
/// <returns>all the users in the room</returns>
vector<string> Room::getAllUsers() const
{
	vector<string> users; // vector of usernames

	for (LoggedUser user : m_users)
	{
		users.push_back(user.getUsername());
	}

	return users;
}