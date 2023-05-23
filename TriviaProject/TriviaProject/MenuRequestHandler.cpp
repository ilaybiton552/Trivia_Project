#include "MenuRequestHandler.h"

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
    if (requestInfo.id == SIGNOUT_CODE)
    {
        return signout(requestInfo);
    }

    if (requestInfo.id == GET_ROOM_CODE)
    {
        return getRooms(requestInfo);
    }

    if (requestInfo.id == GET_PLAYERS_CODE)
    {
        return getPlayersInRoom(requestInfo);
    }

    if (requestInfo.id == GET_STATS_CODE)
    {
        return getPersonalStats(requestInfo);
    }

    if (requestInfo.id == GET_HIGH_SCORE_CODE)
    {
        return getHighScore(requestInfo);
    }

    if (requestInfo.id == JOIN_ROOM_CODE)
    {
        return joinRoom(requestInfo);
    }

    return createRoom(requestInfo);
}

RequestResult MenuRequestHandler::signout(const RequestInfo request)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo request)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo request)
{
    return RequestResult();
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
