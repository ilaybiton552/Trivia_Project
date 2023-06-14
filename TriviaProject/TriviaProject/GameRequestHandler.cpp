#include "GameRequestHandler.h"

/// <summary>
/// Constructor of GameRequestHandler
/// </summary>
/// <param name="game">Game, the game</param>
/// <param name="loggedUser">LoggedUser, the user</param>
/// <param name="gameManager">GameManager, the game manager</param>
/// <param name="handlerFactory">RequestHandlerFactory, the handler factory</param>
GameRequestHandler::GameRequestHandler(Game& game, const LoggedUser& loggedUser, GameManager& gameManager, RequestHandlerFactory& handlerFactory)
	: m_game(game), m_user(loggedUser), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
}

/// <summary>
/// Checks if the request of the client is relevant
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>bool, if the request is relevant</returns>
bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return requestInfo.id <= GET_GAME_RESULT_CODE && requestInfo.id >= LEAVE_GAME_CODE;
}

/// <summary>
/// Getter for game
/// </summary>
/// <returns>Game, the game of the handler</returns>
Game GameRequestHandler::getGame() const
{
	return m_game;
}
