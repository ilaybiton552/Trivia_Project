#include "RoomAdminRequestHandler.h"

/// <summary>
/// Constrcutor of RoomAdminRequestHandler
/// </summary>
/// <param name="user">LoggedUser, the logged user</param>
/// <param name="room">Room, the room</param>
/// <param name="roomManager">RoomManger, the room manager</param>
/// <param name="handlerFactory">RequestHandlerFactory, the handler factory</param>
RoomAdminRequestHandler::RoomAdminRequestHandler(const LoggedUser& user, const Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory)
	: m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

/// <summary>
/// Checks if the request is relevant
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>bool, true if the request is relevant and false otherwise</returns>
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.id <= GET_ROOM_STATE_CODE && requestInfo.id >= CLOSE_ROOM_CODE;
}

/// <summary>
/// Handles the request of the client
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	switch (requestInfo.id)
	{
	case CLOSE_ROOM_CODE:
		return closeRoom(requestInfo);
	case START_GAME_CODE:
		return startGame(requestInfo);
	case GET_ROOM_STATE_CODE:
		return getRoomState(requestInfo);
	}
	return RequestResult();
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
