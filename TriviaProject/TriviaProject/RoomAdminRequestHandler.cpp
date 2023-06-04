#include "RoomAdminRequestHandler.h"

/// <summary>
/// Constrcutor of RoomAdminRequestHandler
/// </summary>
/// <param name="user">LoggedUser, the user</param>
/// <param name="room">Room, the room</param>
/// <param name="roomManager">RoomManger, the room manager</param>
/// <param name="handlerFactory">RequestHandlerFactory, the handler factory</param>
RoomAdminRequestHandler::RoomAdminRequestHandler(const LoggedUser& user, const Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory)
	: m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{

}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{

}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo)
{

}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo)
{

}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo)
{

}
