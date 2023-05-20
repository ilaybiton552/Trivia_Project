#pragma once
#include <map>
#include "LoggedUser.h"
#include "Room.h"
#include "Structs.h"

using std::map;
using std::pair;


class RoomManager
{
public:
	//Methods
	bool createRoom(const LoggedUser loggedUser, RoomData roomData);
	bool deleteRoom(int ID);
	//Getters
	unsigned int getRoomState(const int ID);
	vector<RoomData> getRooms();
	Room& getRoom(const int ID);

private:
	//Field
	map<unsigned int, Room> m_rooms; // <roomID, Room>
};

