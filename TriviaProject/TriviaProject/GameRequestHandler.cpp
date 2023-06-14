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
