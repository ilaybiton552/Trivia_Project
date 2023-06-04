#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

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

/// <summary>
/// Gets the state of the room
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result of the requst</returns>
RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo)
{
	RequestResult result;

	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(m_room.getRoomState());

	return result;
}
