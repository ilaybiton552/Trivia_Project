#include "MenuRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

/// <summary>
/// Constructor of MenuRequestHandler
/// </summary>
/// <param name="user">LoggedUser, the user that logged</param>
/// <param name="roomManager">reference of RoomManager, the room manager</param>
/// <param name="statisticsManager">reference of StatisticsManager, the statistics manager</param>
/// <param name="handlerFactory">reference of RequestHandlerFactory, the handler factory</param>
MenuRequestHandler::MenuRequestHandler(const LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory) : 
    m_user(user), m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory)
{
}

/// <summary>
/// Checks if the request is relevant
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>bool, true if the request is relevant and false otherwise</returns>
bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return (requestInfo.id <= CREATE_ROOM_CODE && requestInfo.id >= SIGNOUT_CODE);
}

/// <summary>
/// Handles the request
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the user's request</returns>
RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    switch ((CODES)requestInfo.id)
    {
    case SIGNOUT_CODE:
        return signout(requestInfo);
    case GET_ROOM_CODE:
        return getRooms(requestInfo);
    case GET_PLAYERS_CODE:
        return getPlayersInRoom(requestInfo);
    case GET_STATS_CODE:
        return getPersonalStats(requestInfo);
    case GET_HIGH_SCORE_CODE:
        return getHighScore(requestInfo);
    case JOIN_ROOM_CODE:
        return joinRoom(requestInfo);
    case CREATE_ROOM_CODE:
        return createRoom(requestInfo);
    }
    return RequestResult();
}

/// <summary>
/// Sign out a user
/// </summary>
/// <param name="request"RequestInfo, the information of the request></param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult MenuRequestHandler::signout(const RequestInfo request)
{
    RequestResult result;

    result.newHandler = m_handlerFactory.createLoginRequestHandler();
    LogoutResponse response = { m_handlerFactory.getLoginManager().logout(m_user.getUsername()) };
    result.response = JsonResponsePacketSerializer::serializeResponse(response);

    return result;
}

/// <summary>
/// Gets list of the rooms
/// </summary>
/// <param name="request">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult MenuRequestHandler::getRooms(const RequestInfo request)
{
    RequestResult result;

    result.newHandler = nullptr; // don't want to change the handler
    GetRoomResponse response = { m_roomManager.getRooms() };
    result.response = JsonResponsePacketSerializer::serializeResponse(response);

    return result;
}

/// <summary>
/// Gets list of players in a room
/// </summary>
/// <param name="request">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo request)
{
    RequestResult result;

    result.newHandler = nullptr; // don't want to change the handler
    GetPlayersInRoomRequest requestData = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(request.buffer);
    GetPlayersInRoomResponse response = { m_roomManager.getRoom(requestData.roomId).getAllUsers() };
    result.response = JsonResponsePacketSerializer::serializeResponse(response);

    return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo request)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo request)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo request)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo request)
{
    return RequestResult();
}
