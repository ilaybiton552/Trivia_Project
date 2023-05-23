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

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    return RequestResult();
}
