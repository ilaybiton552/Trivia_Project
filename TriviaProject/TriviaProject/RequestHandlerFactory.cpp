#include "RequestHandlerFactory.h"

/// <summary>
/// Constructor of ReqeusetHandlerFactory
/// </summary>
/// <param name="database">pointer of IDatabase, the database of the program</param>
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database), m_statisticsManager(database)
{
	m_database = database;
	m_roomManager;
}

/// <summary>
/// Creates menu request handler
/// </summary>
/// <param name="loggedUser">LoggedUser, the user that logged to the program</param>
/// <returns>pointer of MenuRequestHandler, the created handler</returns>
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser loggedUser)
{
	return new MenuRequestHandler(loggedUser, m_roomManager, m_statisticsManager, *this);
}

/// <summary>
/// Creates loginRequestHandler
/// </summary>
/// <returns>pointer of LoginRequestHandler, pointer for the login request handler</returns>
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

/// <summary>
/// Creates room admin request handler
/// </summary>
/// <param name="admin">the room admin user</param>
/// <param name="room">the room</param>
/// <returns>pointer of RoomAdminRequestHandler, the created handler</returns>
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser admin, Room room)
{

}

/// <summary>
/// Creates room member request handler
/// </summary>
/// <param name="member">the room member</param>
/// <param name="room">the room</param>
/// <returns>pointer of RoomMemberRequestHandler, the created handler</returns>
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const LoggedUser member, Room room)
{

}

/// <summary>
/// Gets the login manager
/// </summary>
/// <returns>reference of LoginManager, the login manager of the object</returns>
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}

/// <summary>
/// Gets the statistics manager
/// </summary>
/// <returns>reference of StatisticsManager, the statistics manager</returns>
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return m_statisticsManager;
}

/// <summary>
/// Gets the room manager
/// </summary>
/// <returns>reference of RoomManager, the room manager</returns>
RoomManager& RequestHandlerFactory::getRoomManager()
{
	return m_roomManager;
}
