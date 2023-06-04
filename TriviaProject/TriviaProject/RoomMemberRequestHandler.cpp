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

/// <summary>
/// Checks if the request of the client is relevant
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>bool, true if the request is relevant and false otherwise</returns>
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id == GET_ROOM_STATE_CODE || requestInfo.id == LEAVE_ROOM_CODE;
}

/// <summary>
/// Handels the request
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result of the request</returns>
RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo) 
{
	if (requestInfo.id == GET_ROOM_STATE_CODE)
	{
		return getRoomState(requestInfo);
	}
	return leaveRoom(requestInfo);
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
