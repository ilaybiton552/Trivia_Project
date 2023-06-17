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
/// Handlers the request of the client
/// </summary>
/// <param name="requestInfo">RequestInfo, the request of the client</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	switch (requestInfo.id)
	{
	case LEAVE_GAME_CODE:
		return leaveGame(requestInfo);
	case GET_QUESTION_CODE:
		return getQuestion(requestInfo);
	case SUBMIT_ANSWER_CODE:
		return submitAnswer(requestInfo);
	case GET_GAME_RESULT_CODE:
		return getGameResults(requestInfo);
	}
	return RequestResult();
}

/// <summary>
/// Getter for game
/// </summary>
/// <returns>Game, the game of the handler</returns>
Game GameRequestHandler::getGame() const
{
	return m_game;
}

/// <summary>
/// Gets the next question for the client
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult GameRequestHandler::getQuestion(const RequestInfo& requestInfo)
{
	return RequestResult();
}

/// <summary>
/// Submits the answer of the client
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult GameRequestHandler::submitAnswer(const RequestInfo& requestInfo)
{
	return RequestResult();
}

/// <summary>
/// Gets the results of the game
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult GameRequestHandler::getGameResults(const RequestInfo& requestInfo)
{
	return RequestResult();
}

/// <summary>
/// Leaves the game
/// </summary>
/// <param name="requestInfo">RequestInfo, the informtaion of the request</param>
/// <returns>RequestResult, the result of the request</returns>
RequestResult GameRequestHandler::leaveGame(const RequestInfo& requestInfo)
{
	return RequestResult();
}
