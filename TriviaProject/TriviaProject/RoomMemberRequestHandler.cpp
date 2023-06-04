#include "RoomMemberRequestHandler.h"

/// <summary>
/// Constructor of RoomMemberRequestHandler
/// </summary>
/// <param name="user">LoggedUser, the logged user</param>
/// <param name="room">Room, the room</param>
/// <param name="roomManager">RoomManager, the room manager</param>
/// <param name="handlerFactory">RequestHandlerFactory, the request handler factory</param>
RoomMemberRequestHandler::RoomMemberRequestHandler(const LoggedUser& user, const Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory)
	: m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{

}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo) 
{

}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{

}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo)
{

}
