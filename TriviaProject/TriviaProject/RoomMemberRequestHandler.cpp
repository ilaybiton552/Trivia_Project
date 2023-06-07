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
bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return requestInfo.id == GET_ROOM_STATE_CODE || requestInfo.id == LEAVE_ROOM_CODE;
}

/// <summary>
/// Handels the request
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result of the request</returns>
RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo) 
{
	if (requestInfo.id == GET_ROOM_STATE_CODE)
	{
		return getRoomState(requestInfo);
	}
	return leaveRoom(requestInfo);
}

/// <summary>
/// Gets the id of the room
/// </summary>
/// <returns>Room, the room</returns>
Room RoomMemberRequestHandler::getRoom() const
{
	return m_room;
}

/// <summary>
/// Getter for m_user
/// </summary>
/// <returns>LoggedUser, the logged user</returns>
LoggedUser RoomMemberRequestHandler::getLoggedUser() const
{
	return m_user;
}

/// <summary>
/// Leaves the room
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result of the request</returns>
RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
	RequestResult result;

	result.newHandler = nullptr;
	LeaveRoomResponse response = { m_room.removeUser(m_user) };
	if (response.status == SUCCESS)
	{
		result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(response);

	return result;
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
