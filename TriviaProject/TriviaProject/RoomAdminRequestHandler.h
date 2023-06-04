#pragma once 
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "Structs.h"

enum CODES {CLOSE_ROOM_CODE = 110, START_GAME_CODE, GET_ROOM_STATE_CODE};
#define SUCCESS 1
#define ACTIVE_ROOM 1

class RequestHandlerFactory;

class RoomAdminRequestHandler
{
public:
	RoomAdminRequestHandler(const LoggedUser& user, const Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);

	//Methods
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	//Fields
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	//Methods
	RequestResult closeRoom(RequestInfo requestInfo);
	RequestResult startGame(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};
