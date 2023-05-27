#include "RoomManager.h"

/// <summary>
/// the function creates a room
/// </summary>
/// <param name="loggedUser">the owner of the room - the first player</param>
/// <param name="roomData">the room data</param>
/// <returns>if the room created</returns>
bool RoomManager::createRoom(const LoggedUser loggedUser, RoomData roomData)
{
	try
	{
		m_rooms.insert(pair<unsigned int, Room>(roomData.id, Room(roomData)));
		m_rooms[roomData.id].addUser(loggedUser);
	}
	catch(...)
	{
		return false;
	}
	return true;
}

/// <summary>
/// the function deletes the room according to its id
/// </summary>
/// <param name="ID">the room id</param>
/// <returns>if the room deleted</returns>
bool RoomManager::deleteRoom(int ID)
{
	try
	{
		m_rooms.erase((unsigned int)ID);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

/// <summary>
/// the function returns room state according to its id
/// </summary>
/// <param name="ID">the room id</param>
/// <returns>the room state</returns>
unsigned int RoomManager::getRoomState(const int ID)
{
	return getRoom(ID).getRoomData().isActive;
}

/// <summary>
/// the function returns vector of rooms
/// </summary>
/// <returns>vector of rooms</returns>
vector<RoomData> RoomManager::getRooms()
{
	vector<RoomData> rooms; // vector of rooms

	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		rooms.push_back(it->second.getRoomData());
	}

	return rooms;
}

/// <summary>
/// the function returns room according to its id
/// </summary>
/// <param name="ID">the room id</param>
/// <returns>the room</returns>
Room& RoomManager::getRoom(const int ID) 
{
	return m_rooms[(unsigned int)ID];
}
