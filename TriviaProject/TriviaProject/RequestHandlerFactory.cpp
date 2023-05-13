#include "RequestHandlerFactory.h"

/// <summary>
/// Constructor of ReqeusetHandlerFactory
/// </summary>
/// <param name="database">pointer of IDatabase, the database of the program</param>
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database)
{
	m_database = database;
}

/// <summary>
/// Creates loginRequestHandler
/// </summary>
/// <returns>pointer of LoginRequestHandler, pointer for the login request handler</returns>
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
	return new LoginRequestHandler();
}

/// <summary>
/// Gets the login manager
/// </summary>
/// <returns>reference of LoginManager, the login manager of the object</returns>
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}
