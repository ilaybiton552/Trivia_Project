#include "RequestHandlerFactory.h"

/// <summary>
/// Constructor of ReqeusetHandlerFactory
/// </summary>
/// <param name="database">pointer of IDatabase, the database of the program</param>
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database), m_statisticsManager(database), m_gameManager(database)
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
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser admin, const Room& room)
{
	return new RoomAdminRequestHandler(admin, room, m_roomManager, *this);
}

/// <summary>
/// Creates room member request handler
/// </summary>
/// <param name="member">the room member</param>
/// <param name="room">the room</param>
/// <returns>pointer of RoomMemberRequestHandler, the created handler</returns>
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const LoggedUser member, const Room& room)
{
	return new RoomMemberRequestHandler(member, room, m_roomManager, *this);
}

/// <summary>
/// Creates game request handler
/// </summary>
/// <param name="loggedUser">LoggedUser, the logged user</param>
/// <param name="game">Game, the game</param>
/// <returns>GameRequestHandler*</returns>
GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const LoggedUser& loggedUser, Game& game)
{
	return new GameRequestHandler(game, loggedUser, m_gameManager, *this);
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

/// <summary>
/// Gets the game manager
/// </summary>
/// <returns>reference of GameManager, the game manager</returns>
GameManager& RequestHandlerFactory::getGameManager()
{
	return m_gameManager;
}
