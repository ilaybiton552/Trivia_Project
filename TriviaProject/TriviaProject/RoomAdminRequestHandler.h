#pragma once 
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "Structs.h"

class RoomAdminRequestHandler
{
public:
	//Methods
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	//Fields
	Room m_room;
	LoggedUser m_user;
	RoomManager m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	//Methods
	RequestResult closeRoom(RequestInfo requestInfo);
	RequestResult startGame(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};