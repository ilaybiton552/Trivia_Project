#include "GameRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

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
	RequestResult result;

	Question question = m_game.getQuestionForUser(m_user);
	vector<string> possibleAnswers = question.getPossibleAnswers();
	map<unsigned int, string> answers;
	for (int i = 0; i < 4; i++)
	{
		answers[i] = possibleAnswers[i];
	}
	GetQuestionResponse response = { SUCCESS, question.getQuestion(), answers };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;

	return result;
}

/// <summary>
/// Submits the answer of the client
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult GameRequestHandler::submitAnswer(const RequestInfo& requestInfo)
{
	RequestResult result;

	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
	SubmitAnswerResponse response = { SUCCESS, m_game.submitAnswer(m_user, request.answerId, request.answerTime, m_handlerFactory.getDatabase()) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;

	return result;
}

/// <summary>
/// Gets the results of the game
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>RequestResult, the result for the request</returns>
RequestResult GameRequestHandler::getGameResults(const RequestInfo& requestInfo)
{
	RequestResult result;

	GetGameResultsResponse response = { SUCCESS }; // need to add vector of results
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);

	return result;
}

/// <summary>
/// Leaves the game
/// </summary>
/// <param name="requestInfo">RequestInfo, the informtaion of the request</param>
/// <returns>RequestResult, the result of the request</returns>
RequestResult GameRequestHandler::leaveGame(const RequestInfo& requestInfo)
{
	RequestResult result;

	m_game.removePlayer(m_user);
	LeaveGameResponse response = { SUCCESS };
	result.newHandler = nullptr;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);

	return result;
}
