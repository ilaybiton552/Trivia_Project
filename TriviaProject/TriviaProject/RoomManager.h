#pragma once
#include <map>
#include "LoggedUser.h"
#include "Room.h"
#include "Structs.h"

using std::map;


class RoomManager
{
public:
	//Methods
	int createRoom(const LoggedUser loggedUser, RoomData roomData);
	int deleteRoom(int ID);
	//Getters
	unsigned int getRoomState(const int ID) const;
	vector<RoomData> getRooms() const;
	Room& getRoom(const int ID);

private:
	//Field
	map<unsigned int, Room> m_rooms; // <roomID, Room>
};

